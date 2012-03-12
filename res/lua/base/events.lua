--[[********************************
--       Events Subsystem
--********************************]]

local Events = {}
local registered = {}

function Events.call(event, ...)
	if not registered[event] then
		return
	end

	for listener in pairs(registered[event]) do
		if type(listener) == "function" then
			listener(event, ...)
		elseif listener[event] then
			listener[event](listener, ...)
		elseif listener.onEvent then
			listener:onEvent(event, ...)
		end
	end
end

function Events.register(listener, event)
	if type(listener) == "string" and type(event) ~= "string" then
		event, listener = listener, event
	end
	if not registered[event] then
		registered[event] = {}
		_G[event] = function(...)
			Events.call(event, ...)
		end
	end

	registered[event][listener] = true
end

function Events.unregister(listener, event)
	if not registered[event] then
		return
	end

	registered[event][listener] = nil
end

function Events.mixin(object)
	object.registerEvent = register
	object.unregisterEvent = unregister
end

return Events
