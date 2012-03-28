local Events = require("base.events")

local FileWatcher = {}
local watched = {}

function FileWatcher.watch(file, func)
	func = func or dofile
	func(file)
	local ts = GameEngine.fileModified(file)
	watched[file] = { ts = ts, func = func}
end

local elapsed = 0
Events.register("onUpdate", function(event, dt)
	elapsed = elapsed + dt
	if elapsed < 0.5 then return end

	elapsed = 0
	for file, data in pairs(watched) do
		local ts = GameEngine.fileModified(file)
		if ts > data.ts then
			data.ts = ts
			data.func(file)
		end
	end
end)

return FileWatcher
