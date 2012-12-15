-- Package FileWatcher regularly checks if a file was modified.
local FileWatcher = {}

local Events = require("base.events")

local watched = {}

-- Watch adds a file to the watch list, firing an "onFileChanged" event every
-- time the file is modified. An optional function can be passed along
-- that will listen to the event.
function FileWatcher.watch(file, func)
	if func then
		Events.register("onFileChanged", func, file)
	end

	watched[file] = GameEngine.fileModified(file)
	Events.call("onFileChanged", file)
end

local elapsed = 0
Events.register("onUpdate", function(event, dt)
	elapsed = elapsed + dt
	if elapsed < 0.5 then return end

	elapsed = 0
	for file, last in pairs(watched) do
		local curr = GameEngine.fileModified(file)
		if curr > last then
			watched[file] = curr
			Events.call("onFileChanged", file)
		end
	end
end)

return FileWatcher
