local make = require("base.make").make
local Game = require("game.main")

local Level = {}
Level.__index = Level

function Level.new()
	return setmetatable({}, Level)
end

function Level:load(data)
	for name, objectData in pairs(data) do
		self[name] = make(objectData)
	end
end

function Level:unload()
	for name in pairs(self) do
		self[name] = nil
	end
end

function Level:register()
	for name, object in pairs(self) do
		Game.register(object.components)
	end
end

function Level:unregister()
	for name, object in pairs(self) do
		Game.unregister(object.components)
	end
end

return Level
