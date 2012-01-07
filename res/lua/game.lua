Game = make("Game", { "EventListener" })
Game.eventListener:registerEvent("onUpdate")
Game.eventListener:registerEvent("onQuit")

function Game:onUpdate(elapsed)
	self.lastUpdate = (self.lastUpdate or 0) + elapsed
	self.frameCount = (self.frameCount or 0) + 1

	if self.lastUpdate > 1 then
		print(self.frameCount)
		self.lastUpdate = 0
		self.frameCount = 0
	end
end

function Game:onQuit()
	print("Adios!")
end
