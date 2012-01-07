--[[********************************
--       Events Subsystem
--********************************]]

Events = {}

local registered = {}

function Events.call(event, ...)
	if not registered[event] then
		return
	end

	for listener in pairs(registered[event]) do
		if type(listener) == "function" then
			listener(event, ...)
		else 
			listener:call(event, ...)
		end
	end
end

function Events.register(event, listener)
	if not registered[event] then
		registered[event] = {}
		_G[event] = function(...)
			Events.call(event, ...)
		end
	end

	registered[event][listener] = true
end

function Events.unregister(event, listener)
	if not registered[event] then
		return
	end

	registered[event][listener] = nil
end


--[[********************************
--     EventListener Component
--********************************]]

EventListener = {}
EventListener.__index = EventListener


function EventListener.new()
	return setmetatable({events = {}}, EventListener)
end

function EventListener:call(event, ...)
	local target = self.parent or self
	target[event](target, ...)
end


function EventListener:registerEvent(event)
	self.events[event] = true
	Events.register(event, self)
end

function EventListener:unregisterEvent(event)
	self.events[event] = nil
	Events.unregister(event, self)
end

function EventListener:register()
	if not disabled then
		return
	end
	disabled = false
	for event in pairs(events) do
		Events.register(event, self)
	end
end

function EventListener:unregister()
	if disabled then
		return
	end
	disabled = true
	for event in pairs(events) do
		Events.unregister(event, self)
	end
end
