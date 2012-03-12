local Events = require("base.events")
local Store = require("base.store")
local Persistence = require("base.persistence")

local Game = {}

function Game.register(components)
	for _, component in pairs(components) do
		if component.register then
			component:register()
		end
	end
end

function Game.unregister(components)
	for _, component in pairs(components) do
		if component.unregister then
			component:unregister()
		end
	end
end

function Game.mixin(self)
	self.register = Game.register
	self.unregister = Game.unregister
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
