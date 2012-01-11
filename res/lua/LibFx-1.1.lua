--[[
Name: LibFx-1.1
Author: Cargor (xconstruct@gmail.com)
Dependencies: LibStub
License: GPL 2
Description: Animations! And these actually work ... unlike Blizz' ones
]]

local MAJOR, MINOR = "LibFx-1.1", 5
local LibFx = { Version = MAJOR}
_G.LibFx = LibFx
if not LibFx then return end

local ramps, anims, running = {}, {}, {}
local numRunning = 0

local mt = {
__index = LibFx,
__call = function(self) self:Start() end,
}


--[[*****************************
	LibFx:RegisterAnimation(name, func, startFunc)
	Registers a new animation for use within LibFx
	-	name = Name of animation
	-	get = Function for getting the initial value
	-	set = Function for setting the value
*******************************]]
function LibFx.RegisterAnimation(name, get, set)
	if(not anims[name]) then
		anims[name] = {Get = get, Set = set}
		return anims[name]
	end
end

function LibFx.GetAnimationByName(name)
	return anims[name]
end

function LibFx.AnimationsIterator()
	return pairs(anims)
end

--[[*****************************
	LibFx:RegisterRamp(name, func)
	Registers a new ramp for use within LibFx
	-	name = Name of ramp
	-	func = Function which returns the value to use
*******************************]]
function LibFx.RegisterRamp(name, func)
	if(not ramps[name]) then ramps[name] = func end
end

function LibFx.GetRampByName(name)
	return ramps[name]
end

function LibFx.RampIterator()
	return pairs(ramps)
end

--[[*****************************
	LibFx.New(fx)
	Creates a new fx-object
	-	fx = table holding options
*******************************]]
function LibFx.New(fx)
	assert(fx, MAJOR..": No fx-table specified")
	fx = setmetatable(fx, mt)
	if(type(fx.anim) == "string") then fx.anim = anims[fx.anim] end
	assert(fx.anim, MAJOR..": Animation not specified")
	if(type(fx.ramp) == "string") then fx.ramp = ramps[fx.ramp] end
	if(not fx.ramp) then fx.ramp = ramps["Linear"] end
	assert(fx.ramp, MAJOR..": Ramp not specified")
	if(not fx.frame) then fx.frame = frame end
	assert(fx.frame, MAJOR..": Frame not specified")
	if(not fx.duration) then fx.duration = 1 end
	return fx
end

--[[*****************************
	LibFx:Start()
	Starts an existing Fx
*******************************]]
function LibFx.Start(fx)
	if(not fx or running[fx]) then return end
	fx.anim.Get(fx)
	fx.runTime = 0
	fx.rDelay = fx.delay
	--if(numRunning == 0) then LibFx.Updater:Show() end
	running[fx] = true
	numRunning = numRunning + 1
	if(fx.onStart) then fx.onStart(fx.frame, fx) end
end

--[[*****************************
	LibFx:Stop()
	Ends an existing Fx
*******************************]]
function LibFx.Stop(fx)
	if(not fx or not running[fx]) then return end

	numRunning = numRunning - 1
	running[fx] = nil
	if(fx.onComplete) then fx.onComplete(fx.frame, fx) end
	--if(numRunning == 0) then LibFx.Updater:Hide() end
	if(fx.loop) then fx:Start() end
end

--[[*****************************
	LibFx:IsRunning()
	Returns wether the fx is currently running
*******************************]]
function LibFx.IsRunning(fx)
	return running[fx]
end

--[[*****************************
	Private functions
*******************************]]

local updateFrame = make("LibFx-Updater", { make = "EventListener" })
updateFrame.eventListener:registerEvent("onUpdate")
function updateFrame:onUpdate(elapsed)
	for fx, _ in pairs(running) do
		if(fx.rDelay) then
			local diff = fx.rDelay-elapsed
			fx.rDelay = diff > 0 and diff or nil
		end
		if(not fx.rDelay) then
			fx.runTime = fx.runTime + elapsed
			local progress = math.max(math.min(fx.runTime/fx.duration, 1), 0)
			fx.progress = fx.ramp and fx.ramp(progress) or progress
			fx.anim.Set(fx)
			if(fx.runTime > fx.duration) then
				fx:Stop()
			end
		end
	end
end
LibFx.Updater = updateFrame



--[[*****************************
	Default functions
*******************************]]
LibFx.RegisterRamp("Linear",      function(percent) return percent end)
LibFx.RegisterRamp("Smooth",      function(percent) return 1/(1+2.7^(-percent*12+6)) end)

LibFx.RegisterAnimation("Alpha", function(fx)
	fx.r, fx.g, fx.b, fx.start = fx.frame:color()
	fx.diff = fx.finish - fx.start
end, function(fx)
	fx.frame:setColor(fx.r,fx.g,fx.b, fx.start + fx.diff * fx.progress)
end)

LibFx.RegisterAnimation("Translate", function(fx)
	fx.xStart, fx.yStart = fx.frame:pos()
	fx.xDiff = fx.xFinish - fx.x
	fx.yDiff = fx.yFinish - fx.y
end, function(fx)
	fx.frame:setPos(fx.xStart + fx.xDiff * fx.progress,
	                fx.yStart + fx.yDiff * fx.progress)
end)
