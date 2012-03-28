local make = require("base.make").make
local Game = require("game.main")

local Level = {}
local meta = {__index = Level}

function Level.new()
	return setmetatable({}, meta)
end

function Level:load(data)
	self.components = self.components or {}
	for name, objectData in pairs(data) do
		self.components[name] = make(objectData)
	end
end

function Level:unload()
	self.components = {}
end

return Level
