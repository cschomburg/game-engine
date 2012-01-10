Game = make("Game", { "EventListener" })
Game.eventListener:registerEvent("onQuit")

function Game:onQuit()
	print("Adios!")
end
