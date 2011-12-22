function make(name, components)
	local object = Object.new(name)
	for _, name in pairs(components) do
		object[name:lower()] = _G[name].new(object)
		object:addComponent(object[name:lower()])
	end
	return object
end

local frameCount, lastUpdate, fps = 0, 0, 0

local total = 0
function OnUpdate(elapsed)
	lastUpdate = lastUpdate + elapsed
	frameCount = frameCount + 1
	total = total + elapsed

	if lastUpdate > 1 then
		--print(frameCount)
		lastUpdate = 0
		frameCount = 0
		--player:component("Positionable"):modifyPos(0, 100)
	end
end

function dump(...)
	local found = {}
	local function dump_r(o)
		if type(o) == 'table' and not found[o] then
			found[o] = true
			local s = '{ '
			for k,v in pairs(o) do
				if type(k) ~= 'number' then k = '"'..tostring(k)..'"' end
				s = s .. '['..k..'] = ' .. dump_r(v) .. ','
			end
			return s .. '} '
		else
			return tostring(o)
		end
	end

	local str = ""
	for i=1, select('#', ...) do
		if str ~= "" then str = str .. ", " end
		str = str .. dump_r(select(i, ...))
	end
	print(str)
end

math.randomseed(os.time())
