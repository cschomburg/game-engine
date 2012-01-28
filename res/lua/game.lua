Game = make("Game", { "EventListener" })
Game.eventListener:registerEvent("onQuit")

function Game:onQuit()
	print("Adios!")
end

Timer = make("Timer", { "EventListener" })
Timer.eventListener:registerEvent("onUpdate")
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

CheckEvents = make("CheckEvents", { "EventListener" })
CheckEvents.eventListener:registerEvent("onUpdate")
CheckEvents.events = {}
function CheckEvents:onUpdate(elapsed)
	for id, event in pairs(self.events) do
		if event() then
			self.events[id] = nil
		end
	end
end

ControlState = {}
function ControlState:onKeyDown(key, char)
	local player = self.player
	if not player then return end


	if key == "`" then
		States.push(UI.Console)
	end
	if key == "w" and player.groundContacts > 0 then
		player.body:applyForceToCenter(0, 50)
	end
	if key == "a" then
		player.xDir = player.xDir -1
	end
	if key == "d" then
		player.xDir = player.xDir + 1
	end
end

function ControlState:onKeyUp(key)
	local player = self.player
	if not player then return end
	if key == "escape" then
		--States.push(UI.MainMenu)
	end
	if key == "a" then
		player.xDir = player.xDir + 1
	end
	if key == "d" then
		player.xDir = player.xDir - 1
	end
	if key == "=" then
		Graphics.setScale(Graphics.scale() * 1.1)
	end
	if key == "-" then
		Graphics.setScale(Graphics.scale() / 1.1)
	end
end
