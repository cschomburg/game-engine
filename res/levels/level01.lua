local sky = make:background("Sky")
do local r = sky.renderable
	r:setShape("box", 200, 150)
	r:setGradient(255/255, 89/255, 0/255, 1, 180/255, 20/255, 0, 1)
	r:setZIndex(-1)
end
sky:register()

local sun = make:background("Sun")
sun.staticPos:setPos(8, 0)
do local r = sun.renderable
	r:setShape("box", 5.12, 5.12)
	r:setTexture("res/images/sun.png")
	r:setZIndex(-0.8)
	r:setParallax(0.8, 0.8)
	r:setBlendMode("add")
end
sun:register()

local ground = make:static("Ground")
ground.body:setShape("box", 100, 1.5)
do local r = ground.renderable
	r:setShape("box", 200, 3)
	r:setColor(0, 0, 0, 1)
end
ground:register()

local tree = make:background("Tree")
tree.staticPos:setPos(5.12, 2.28)
do local r = tree.renderable
	r:setShape("box", 1.5, 1.65)
	r:setTexture("res/images/tree.png")
	r:setColor(0, 0, 0, 1)
end
tree:register()

for i = 0, 500 do
	local grass = make:background()
	grass.staticPos:setPos(-2 + i*0.4, 1.66)
	grass.renderable:setShape("box", 0.77, 0.33)
	grass.renderable:setTexture("res/images/ground/grass"..math.random(1, 3)..".png")
	grass:register()
end

local player = make:player()
player.body:setPos(5.72, 6.56)
player:register()
Graphics.setCamera(player.body)

function player.body:onContactBegin(body)
	print("Contact with "..body:objectID())
end

function player.body:onContactEnd(body)
	print("Contact End with "..body:objectID())
end

local xDir = 0
function onPhysicsUpdate(timestep)
	player.body:applyForceToCenter(xDir * 3, 0)
	local x, y = player.body:linearVelocity()
	player.body:setLinearVelocity(math.clamp(x, -3, 3), y)
end

local LevelState = {}
function LevelState:onKeyDown(key)
	if key == "w" then
		player.body:applyForceToCenter(0, 100)
	end
	if key == "a" then
		xDir = xDir -1
	end
	if key == "d" then
		xDir = xDir + 1
	end
end

function LevelState:onKeyUp(key)
	if key == "Escape" then
		States.push(UI.MainMenu)
	end
	if key == "a" then
		xDir = xDir + 1
	end
	if key == "d" then
		xDir = xDir - 1
	end
end
States.push(LevelState)
