local level = make("Level", { "Body", "Renderable" })
level:setType("background")
level.body:setPos(0, 0)
level.renderable:setShape("box", 200, 150)
level.renderable:setGradient(255/255, 89/255, 0/255, 1, 180/255, 20/255, 0, 1)
level.renderable:setZIndex(-1)
GameEngine:registerObject(level)

local sun = make("Sun", { "Body", "Renderable" })
sun:setType("background")
sun.body:setPos(8, 0)

apply(sun.renderable, {
	shape = { "box", 5.12, 5.12 },
	texture = "res/images/sun.png",
	zIndex = -0.8,
	parallax = { 0.8, 0.8 },
	blendMode = "add",
})
GameEngine:registerObject(sun)

local ground = factory.box(0, 0, 200, 3)
ground:setName("Ground")
ground:setType("static")
GameEngine:registerObject(ground)

local tree = make("Tree", { "Body", "Renderable" })
tree:setType("background")
tree.body:setPos(5.12, 2.28)
do local r = tree.renderable
	r:setShape("box", 1.5, 1.65)
	r:setTexture("res/images/tree.png")
	r:setColor(0, 0, 0, 1)
end
GameEngine:registerObject(tree)

for i = 0, 500 do
	local name = "Grass"..i
	local grass = make(name, { "Body", "Renderable" })
	grass:setType("background")
	grass.body:setPos(-2 + i*0.4, 1.66)
	grass.renderable:setShape("box", 0.77, 0.33)
	grass.renderable:setTexture("res/images/ground/grass"..math.random(1, 3)..".png")
	GameEngine:registerObject(grass)
end

local player = factory.box(5.72, 6.56, 0.5)
player.renderable:setTexture("res/images/foo.png")
GameEngine:registerObject(player)
GameEngine:setPlayer(player)

local enemy = factory.box(4.72, 6.56, 0.32, 0.32)
enemy.renderable:setTexture("res/images/foo.png")
GameEngine:registerObject(enemy)
