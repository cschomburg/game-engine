package.path = "./res/lua/?.lua;"..package.path
math.randomseed(os.time())
require("env")

local Events = require("base.events")
local Game = require("game.main")
local States = require("game.states")
local ControlState = require("game.states.control")
local UI = require("ui.main")

Events.call("onInit")

local level = dofile("res/lua/levels/01.lua")
level:register()

local player = level.Player
player.body = player.components.Body
player.xDir = 0
player.groundContacts = 0
ControlState.player = player
Graphics.setCamera(player.body)
States.push(ControlState)

function player.body:onContactBegin(other)
	if not other.parent.noGround then
		self.parent.groundContacts = self.parent.groundContacts + 1
	end
end

function player.body:onContactEnd(other)
	if not other.parent.noGround then
		self.parent.groundContacts = self.parent.groundContacts - 1
	end
end

Events.register("onPhysicsUpdate", function(dt)
	player.body:applyForceToCenter(player.xDir, 0)
	local x, y = player.body:linearVelocity()
	player.body:setLinearVelocity(math.clamp(x, -3, 3), y)

	local x, y = player.body:pos()
	if y < - 30 then
		player.body:setLinearVelocity(0, 0)
		player.body:setAngularVelocity(0)
		player.body:setPos(0, 1)
		player.body:setAngle(0)
	end
end)
