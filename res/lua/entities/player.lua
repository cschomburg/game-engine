local Events = require("base.events")
local make = require("base.make").newMake
local Game = require("game.main")

local Player = {}
local meta = {__index = Player}

function Player:register()
	self.comp.Body:setFixedRotation(true)
	Events.register("onPhysicsUpdate", self)
	Events.register("onContactBegin", self, self.comp.Body)
	Events.register("onContactEnd", self, self.comp.Body)
end

function Player:unregister()
	Events.unregister("onPhysicsUpdate", self)
	Events.unregister("onContactBegin", self, self.comp.Body)
	Events.unregister("onContactEnd", self, self.comp.Body)
end

function Player:onPhysicsUpdate()
	local body = self.comp.Body
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

function Player:onContactBegin(body, other)
	self.groundContacts = self.groundContacts + 1
end

function Player:onContactEnd(body, other)
	self.groundContacts = self.groundContacts - 1
end

function Player.new()
	local player = make{Body, SolidRenderable}
	player.comp.Body:setPos(0, 1)
	player.comp.Body:setShape("box", 0.1, 0.25)
	player.comp.SolidRenderable:setAnchor(player.comp.Body)
	player.comp.SolidRenderable:setBoundingRect(0.24, 0.54)
	player.comp.SolidRenderable:setColor(0, 0, 0, 1)

	player.xDir = 0
	player.groundContacts = 0

	setmetatable(player, meta)

	return player
end

return Player
