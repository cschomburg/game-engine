local Events = require("events")

local States = {}
local stack = {}

function States.call(func, ...)
	for i=#stack, 1, -1 do
		if call(stack[i], func, ...) then
			return
		end
	end
end

function States.callTop(func, ...)
	if #stack == 0 then return end
	call(States.top(), func, ...)
end

function States.push(state)
	States.callTop("onSuspend")
	stack[#stack+1] = state
	States.callTop("onEnter")
end

function States.pop()
	if #stack == 0 then
		return
	end
	States.callTop("onLeave")
	stack[#stack] = nil
	States.callTop("onResume")
end

function States.top()
	return stack[#stack]
end

Events.register("onKeyDown", States.call)
Events.register("onKeyUp", States.call)

return States
