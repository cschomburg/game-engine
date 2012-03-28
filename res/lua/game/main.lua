local Events = require("base.events")
local Store = require("base.store")
local Persistence = require("base.persistence")

local Game = {}

function Game.register(object)
	if object.register then
		object:register()
	end
	if object.components then
		for _, component in pairs(object.components) do
			Game.register(component)
		end
	end
end

function Game.unregister(object)
	if object.unregister then
		object:unregister()
	end
	if object.components then
		for _, component in pairs(object.components) do
			Game.unregister(component)
		end
	end
end

local Timer = {}
Game.timer = Timer
Events.register("onUpdate", Timer)
Timer.events = {}

function Timer:onUpdate(elapsed)
	self.total = (self.total or 0) + elapsed
	for time, event in pairs(self.events) do
		if self.total > time then
			self.events[time] = nil
			event()
		end
	end
end

function Timer:register(when, func)
	self.events[self.total+when] = func
end

local CheckEvents = {}
Game.checkEvents = CheckEvents
Events.register("onUpdate", CheckEvents)
CheckEvents.events = {}
function CheckEvents:onUpdate(elapsed)
	for id, event in pairs(self.events) do
		if event() then
			self.events[id] = nil
		end
	end
end

Events.register("onQuit", function()
	Persistence.store("config.lua", Store:get("config"))
end)
Events.register("onInit", function()
	Store:new("config", Persistence.load("config.lua"))
end)

Events.call("onInit")

return Game
