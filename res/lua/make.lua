local Object = {}
Object.__index = Object

schematics = {}

make = {}
local guid = 1
function make:make(name, components)
	if not name then
		name = guid
		guid = guid + 1
	end
	if not components then
		components = { "Body", "Renderable" }
	end
	local object = setmetatable({}, Object)
	object.components = {}
	for _, cType in pairs(components) do
		local component = _G[cType].new(name)
		component.object = object
		object[cType:lowercap()] = component
		object.components[cType] = component
	end
	return object
end
setmetatable(make, {__call = make.make})

function make:background(name)
	local object = make(name, { "StaticPos", "Renderable" })
	object.renderable:setPositionable(object.staticPos)
	return object
end

function make:static(name)
	local object = make(name, { "Body", "Renderable" })
	object.body:setType("static")
	object.renderable:setPositionable(object.body)
	return object
end

function make:dynamic(name)
	local object = make(name, { "Body", "Renderable" })
	object.renderable:setPositionable(object.body)
	return object
end

function make:player(name)
	local object = make:dynamic(name or "Player")
	object.body:setShape("box", 0.25, 0.25)
	object.renderable:setShape("box", 0.5, 0.5)
	object.renderable:setTexture("res/images/foo.png")
	return object
end

function Object:register()
	for _, component in pairs(self.components) do
		if component.register then
			component:register()
		end
	end
end

function Object:unregister()
	for _, component in pairs(self.components) do
		if component.unregister then
			component:unregister()
		end
	end
end
