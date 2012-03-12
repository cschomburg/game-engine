local selector = require("base.selector").get

local Make = {}
local mixins = {}
Make.mixins = mixins

local applyProperty
local function apply(self, data)
	if data == true then return end

	if data.mixins then
		for i, mixin in ipairs(data.mixins) do
			if type(mixin) == "table" then
				mixin = mixin.mixin or mixin
			end
			if type(mixin) == "string" then
				mixin = mixins[mixin] or mixin
			else
			end
			if not type(mixin) == "function" then
				error("Unknown mixin '"..mixin.."'")
			end
			mixin(self, data)
		end
	end

	if data.name then
		self.name = name
	end

	for key, value in pairs(data) do
		if key ~= "mixins" and key ~= "name" then
			applyProperty(self, key, value)
		end
	end
end
Make.apply = apply

local function add(self, cType)
	if not _G[cType] then
		error("No component named '"..cType.."' found!")
	end
	if not _G[cType].new then
		error("Component '"..cType.."' cannot be created!")
	end
	local component = _G[cType].new()
	component.parent = self
	self.components = self.components or {}
	self.components[cType] = component
	self[cType] = component
end

local function parseValue(self, value)
	if type(value) ~= "string" then return value end

	local ch = value:sub(1,1)
	if ch == "$" or ch == ":" then
		value = selector(self, value)
	end

	return value
end

function applyProperty(self, key, value)
	if not key:islowercap() then
		if not self.components or not self.components[key] then
			add(self, key)
		end
		apply(self.components[key], value)
	else
		local func = self["set"..key:uppercap()]
		if not func then
			error("Unknown property '"..key.."'")
		end
		if type(value) == "table" then
			func(self, unpack(value))
		else
			value = parseValue(self, value)
			func(self, value)
		end
	end
	-- TODO: selectors
end

function Make.mixin(self)
	object.apply = apply
	object.add = add
end

function Make.make(data)
	local object = {}
	apply(object, data)
	return object
end

return Make
