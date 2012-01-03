
function make(name, components)
	if not components then
		components = { "Body", "Renderable" }
	end
	local object = {}
	object.components = {}
	for _, name in pairs(components) do
		local component = _G[name].new(name)
		object[name:lower()] = component
		object.components[name] = component
	end
	return object
end

function register(object)
	for _, component in pairs(object.components) do
		component:register()
	end
end

function apply(instance, params)
	if not instance or not params then return end

	for key, value in pairs(params) do
		local methodName = "set"..key:sub(1,1):upper()..key:sub(2)
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
function OnUpdate(elapsed)
	lastUpdate = lastUpdate + elapsed
	frameCount = frameCount + 1
	total = total + elapsed

	if lastUpdate > 1 then
		--print(frameCount)
		lastUpdate = 0
		frameCount = 0
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
