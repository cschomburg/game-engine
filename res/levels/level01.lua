local level = make("Level", { "StaticPos", "Renderable" })
level.staticPos:setPos(0, 0)
level.renderable:setPositionable(level.staticPos)
level.renderable:setShape("box", 200, 150)
level.renderable:setGradient(255/255, 89/255, 0/255, 1, 180/255, 20/255, 0, 1)
level.renderable:setZIndex(-1)
register(level)

local sun = make("Sun", { "StaticPos", "Renderable" })
sun.staticPos:setPos(8, 0)
apply(sun.renderable, {
	positionable = {sun.staticPos},
	shape = { "box", 5.12, 5.12 },
	texture = "res/images/sun.png",
	zIndex = -0.8,
	parallax = { 0.8, 0.8 },
	blendMode = "add",
})
register(sun)

local ground = make("Ground", { "Body", "Renderable" })
ground.body:setType("static")
ground.body:setShape("box", 100, 1.5)
ground.renderable:setPositionable(ground.body)
ground.renderable:setShape("box", 200, 3)
ground.renderable:setColor(0, 0, 0, 1)
register(ground)

local tree = make("Tree", { "Body", "Renderable" })
tree.body:setType("static")
tree.body:setPos(5.12, 2.28)
do local r = tree.renderable
	r:setPositionable(tree.body)
	r:setShape("box", 1.5, 1.65)
	r:setTexture("res/images/tree.png")
	r:setColor(0, 0, 0, 1)
end
register(tree)

for i = 0, 500 do
	local name = "Grass"..i
	local grass = make(name, { "StaticPos", "Renderable" })
	grass.staticPos:setPos(-2 + i*0.4, 1.66)
	grass.renderable:setPositionable(grass.staticPos)
	grass.renderable:setShape("box", 0.77, 0.33)
	grass.renderable:setTexture("res/images/ground/grass"..math.random(1, 3)..".png")
	register(grass)
end

local player = make("Player", { "Body", "Renderable" })
player.body:setPos(5.72, 6.56)
player.body:setShape("box", 0.25, 0.25)
player.renderable:setPositionable(player.body)
player.renderable:setShape("box", 0.5, 0.5)
player.renderable:setTexture("res/images/foo.png")
register(player)
Graphics.setCamera(player.body)

function onKeyUp(key)
	print(key)
	if key == " " then
		if tree.unregistered then
			register(tree)
		else
			unregister(tree)
			print("unregister")
		end
		tree.unregistered = not tree.unregistered
	end
end
