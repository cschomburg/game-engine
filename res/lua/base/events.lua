-- Package Events provides a simple signal-slot system where multiple functions
-- can be notified if a certain condition was met.
--
-- Example:
--     local function printA(event, x) print("a", x) end
--     local function printB() print("b") end
--     Events.register("onSomeCondition", printVar)
--     Events.register("onSomeCondition", printVar, 5)
--     Events.call("onSomeCondition", 3)
--         => prints: "a", 3
--     Events.call("onSomeCondition", 5)
--         => prints: "a", 5
--         => prints "b"
--
local Events = {}
local registered = {}

-- Call fires an event with the specified arguments, informing all
-- listeners on this event as long the event passes their filters.
function Events.call(event, ...)
	if not registered[event] then
		return
	end

	for listener, filters in pairs(registered[event]) do
		local ignored = false
		for i, filter in ipairs(filters) do
			if type(filter) == "function" then
				ignored = not filter(event, ...)
			else
				ignored = select(i, ...) ~= filter
			end
			if ignored then break end
		end

		if not ignored then
			if type(listener) == "function" then
				listener(event, ...)
			elseif type(listener) == "thread" then
				registered[event][listener] = nil
				coroutine.resume(listener, event, ...)
			elseif type(listener) == "table" then
				if listener[event] then
					listener[event](listener, ...)
				end
			end
		end
	end
end

-- Register adds a new listener to an event.
-- A listener can be a function that will be called, a coroutine which will be
-- resumed, or an object that contains a function with the same name as the event.
-- A number of filters can be passed that either must match the event argument
-- at the specific position or, if a function, return true to pass the event to
-- the listener.
function Events.register(event, listener, ...)
	registered[event] = registered[event] or {}
	registered[event][listener] = {...}
end

-- Unregister removes a listener from an event.
function Events.unregister(event, listener)
	if not registered[event] then return end
	registered[event][listener] = nil
end

-- Wait blocks a coroutine until the specified event (with filters) fires.
function Events.wait(event, ...)
	local co = coroutine.running()
	assert(co, "The main thread cannot wait!")
	Events.register(event, co, ...)
	return coroutine.yield()
end

-- Co wraps the function to run in a new coroutine each time it is called.
-- Useful together with Events.wait()
function Events.co(func)
	return function(...)
		return coroutine.resume(coroutine.create(func), ...)
	end
end

return Events
