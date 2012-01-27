local background = make:background("Background")
background.renderable:setShape("box", 10.24, 10.24)
background.renderable:setTexture("res/images/background/tile-1.png")
--background.renderable:setColor(159/255, 96/255, 65/255, 1)
background.renderable:setParallax(1, 1)
background:register()

local noise = make:background("Noise")
noise.renderable:setShape("box", 20.24, 20.24)
noise.renderable:setTexture("res/images/effects/noise.png")
noise.renderable:setParallax(1, 1)
noise.renderable:setZIndex(1)
noise.renderable:setColor(1, 1, 1, 0.2)
noise:register()

--[[
local sun = make:background("Sun")
sun.renderable:setShape("box", 4, 4)
sun.renderable:setBlendMode("add")
sun.renderable:setTexture("res/images/sun.png")
sun.renderable:setParallax(0.9, 0.9)
sun:register()
]]

local sun = make:background("Sun")
sun.renderable:setShape("box", 10.24, 10.24)
sun.renderable:setBlendMode("add")
sun.renderable:setTexture("res/images/background/sun1.png")
sun.renderable:setParallax(0.99, 0.99)
sun:register()

--[[
local sunEffect = make:background("Sun")
sunEffect.renderable:setShape("box", 2, 2)
sunEffect.renderable:setBlendMode("add")
sunEffect.renderable:setTexture("res/images/sun.png")
sunEffect.renderable:setParallax(0.9, 0.9)
sunEffect.renderable:setColor(1, 1, 1, 0.2)
sunEffect.renderable:setZIndex(1)
sunEffect:register()
]]

local cloud1 = make:background()
cloud1.staticPos:setPos(0, -28)
cloud1.renderable:setShape("box", 9.47, 3.65)
cloud1.renderable:setTexture("res/images/clouds/layer1.png")
cloud1.renderable:setParallax(0.9, 0.9)
cloud1:register()

local cloud2 = make:background()
cloud2.staticPos:setPos(18, 14)
cloud2.renderable:setShape("box", 3.71, 3.13)
cloud2.renderable:setTexture("res/images/clouds/single1.png")
cloud2.renderable:setParallax(0.8, 0.8)
cloud2:register()

--[[
local cloud3 = make:background()
cloud3.staticPos:setPos(-18, 14)
cloud3.renderable:setShape("box", 5.64, 3.71)
cloud3.renderable:setTexture("res/images/clouds/layer2.png")
cloud3.renderable:setParallax(0.9, 0.9)
cloud3:register()
]]

local island = make:static("Island")
island.body:setShape("box", 1, 0.64)
island.renderable:setShape("box", 2.02, 1.4)
island.renderable:setTexture("res/images/island.png")
island:register()

local tree = make:background("Tree")
tree.staticPos:setPos(0, 1.3)
tree.renderable:setShape("box", 2.23*3/5, 2.26*3/5)
tree.renderable:setTexture("res/images/background/tree2.png")
tree:register()

local player = make:dynamic("Player")
player.body:setShape("box", 0.1, 0.25)
player.renderable:setShape("box", 0.2, 0.5)
player.renderable:setColor(0, 0, 0, 1)
player.xDir = 0
player.groundContacts = 0
player.body:setPos(0, 1)
player:register()
--player.body:setGravityScale(0)
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

function onPhysicsUpdate(timestep)
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
end
