local States = {}
_G.States = States

local states = {}

local function callTop(func, ...)
	if #states > 0 then
		call(states[#states], func, ...)
	end
end

function States.push(state)
	callTop("onSuspend")
	states[#states+1] = state
	callTop("onEnter")
end

function States.pop()
	if #states == 0 then
		return
	end
	callTop("onLeave")
	states[#states] = nil
	callTop("onResume")
end

function States.current()
	return states[#states]
end

function onKeyDown(...) callTop("onKeyDown", ...) end
function onKeyUp(...) callTop("onKeyUp", ...) end
