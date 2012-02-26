local Console = require("console")
local States = require("states")

local ControlState = {}

function ControlState:onKeyDown(key, char)
	local player = self.player
	if not player then return end

	if key == "`" then
		States.push(Console)
	end
	if key == "w" and player.groundContacts > 0 then
		player.Body:applyForceToCenter(0, 50)
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

return ControlState
