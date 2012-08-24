local Game = require("game.main")
local Console = require("ui.console")
local States = require("game.states")
local make = require("base.make").newMake

local DebugState = {}

function DebugState:onKeyDown(key, char)
	if key == "`" then
		States.push(Console)
	end
end

function DebugState:onKeyUp(key)
	if key == "=" then
		Graphics.setScale(Graphics.scale() * 1.1)
	end
	if key == "-" then
		Graphics.setScale(Graphics.scale() / 1.1)
	end
end

function DebugState:onMouseButtonDown(button, x, y)
	x, y = Graphics.toWorldPos(x, y)
	print(x, y)
	local cube = make{Body, SolidRenderable}
	cube.comp.Body:setType("static")
	cube.comp.Body:setPos(x, y)
	cube.comp.Body:setShape("box", 0.5, 0.5)
	cube.comp.SolidRenderable:setAnchor(cube.comp.Body)
	cube.comp.SolidRenderable:setBoundingRect(1, 1)
	cube.comp.SolidRenderable:setColor(0, 0, 0, 1)
	Game.register(cube)
end

return DebugState
