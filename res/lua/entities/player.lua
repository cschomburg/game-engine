local Events = require("base.events")
local make = require("base.make").make
local Game = require("game.main")

local Player = {}
local meta = {__index = Player}

function Player:register()
	Events.register("onPhysicsUpdate", self)
end

function Player:unregister()
	Events.unregister("onPhysicsUpdate", self)
end

function Player:onPhysicsUpdate()
	do local body = self.Body
		body:applyForceToCenter(player.xDir, 0)
		local x, y = body:linearVelocity()
		body:setLinearVelocity(math.clamp(x, -3, 3), y)

		local x, y = body:pos()
		if y < - 30 then
			body:setLinearVelocity(0, 0)
			body:setAngularVelocity(0)
			body:setPos(0, 1)
			body:setAngle(0)
		end
	end
end

local function PlayerBody_onContactBegin(self, other)
	self.parent.groundContacts = self.parent.groundContacts + 1
end

local function PlayerBody_onContactEnd(self, other)
	self.parent.groundContacts = self.parent.groundContacts - 1
end

function Player.new()
	local player = make{
		Body = {
			pos = {0, 1},
			shape = {"box", 0.1, 0.25},
		},
		SolidRenderable = {
			positionable = "$.Body",
			boundingRect = {0.24, 0.54},
			color = {0, 0, 0, 1},
		},
	}

	player.xDir = 0
	player.groundContacts = 0

	setmetatable(player, meta)

	player.Body.onContactBegin = PlayerBody_onContactBegin
	player.Body.onContactEnd = PlayerBody_onContactEnd

	return player
end

return Player
