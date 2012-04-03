--[[********************************
--          Event Listener
--********************************]]

local Events = require("base.events")

local EventListener = {}
local meta = {__index = EventListener}

function EventListener.new()
	return setmetatable({}, meta)
end

EventListener.type = "EventListener"

function EventListener:listen(events)
	self.events = events
end

function EventListener:register()
	if not self.events then return end

	local target = self.parent or self
	for i, event in ipairs(self.events) do
		Events.register(event, target)
	end
end

function EventListener:unregister()
	if not self.events then return end

	local target = self.parent or self
	for i, event in ipairs(self.events) do
		Events.unregister(target, event)
	end
end

return EventListener
