function string:capitalize()
	return self:sub(1,1):upper()..self:sub(2)
end

function string:lowercap()
	return self:sub(1,1):lower()..self:sub(2)
end

function make(name, components)
	if not components then
		components = { "Body", "Renderable" }
	end
	local object = setmetatable({}, objectMeta)
	object.components = {}
	for _, cType in pairs(components) do
		local component = _G[cType].new(name)
		component.object = object
		object[cType:lowercap()] = component
		object.components[cType] = component
	end
	return object
end

function register(object)
	for _, component in pairs(object.components) do
		if component.register then
			component:register()
		end
	end
end

function unregister(object)
	for _, component in pairs(object.components) do
		if component.unregister then
			component:unregister()
		end
	end
end

function apply(instance, params)
	if not instance or not params then return end

	for key, value in pairs(params) do
		local methodName = "set"..key:capitalize()
		local method = instance[methodName]
		if type(method) == "function" then
			if type(value) == "table" then
				method(instance, unpack(value))
			else
				method(instance, value)
			end
		end
	end
end

--[[--------------
	Other stuff
-----------------]]

local frameCount, lastUpdate, fps = 0, 0, 0

local total = 0
function onUpdate(elapsed)
	lastUpdate = lastUpdate + elapsed
	frameCount = frameCount + 1
	total = total + elapsed

	if lastUpdate > 1 then
		print(frameCount)
		lastUpdate = 0
		frameCount = 0
	end
end

function dump(...)
	local found = {}
	local function dump_r(o)
		if type(o) == 'table' and not found[o] then
			found[o] = true
			local s = '{\n'
			for k,v in pairs(o) do
				if type(k) ~= 'number' then k = '"'..tostring(k)..'"' end
				s = s .. '\t['..k..'] = ' .. dump_r(v):gsub("\n", "\n\t") .. ','
				s = s.."\n"
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

function onQuit()
	print ("Bye!")
end

math.randomseed(os.time())
