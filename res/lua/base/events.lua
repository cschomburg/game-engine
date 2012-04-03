--[[********************************
--       Events Subsystem
--********************************]]

local Events = {}
local registered = {}

function Events.call(event, ...)
	if not registered[event] then
		return
	end

	for destination, filters in pairs(registered[event]) do
		local ignored = false
		for i, filter in ipairs(filters) do
			local arg = select(i, ...)
			if type(filter) == "function" then
				ignored = not filter(arg)
			else
				ignored = arg ~= filter
			end
			if ignored then break end
		end

		if not ignored then
			if type(destination) == "function" then
				destination(event, ...)
			elseif destination[event] then
				destination[event](destination, ...)
			end
		end
	end
end

function Events.register(event, destination, filters)
	registered[event] = registered[event] or {}
	registered[event][destination] = {filters}
end

function Events.unregister(event, destination)
	registered[event][destination] = nil
end

eventhandler = Events.call

return Events
