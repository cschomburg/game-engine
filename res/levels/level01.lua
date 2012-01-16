function make:cube()
	local object = make(name, { "Body", "Renderable" })
	object.body:setShape("box", 0.25, 0.25)
	object.body:setType("static")
	object.isGround = true
	object.renderable:setPositionable(object.body)
	object.renderable:setShape("box", 0.5, 0.5)
	object.renderable:setColor(0.3, 0.3, 0.3, 0)
	return object
end

function make:player()
	local object = make:dynamic(name or "Player")
	object.body:setShape("box", 0.25, 0.25)
	object.renderable:setShape("box", 0.5, 0.5)
	object.renderable:setColor(0.3, 0.3, 0.3, 0)
	return object
end

local function fadeIn(object, duration, delay)
	LibFx.New({
		frame = object,
		anim = "Alpha",
		finish = 1,
		duration = duration or 0.3,
		delay = delay,
	})()
end

local timer = make("Timer", { "EventListener" })
timer.eventListener:registerEvent("onUpdate")
timer.events = {}
function timer:onUpdate(elapsed)
	self.total = (self.total or 0) + elapsed
	for time, event in pairs(self.events) do
		if self.total > time then
			self.events[time] = nil
			event()
		end
	end
end

local checkEvents = make("Timer", { "EventListener" })
checkEvents.eventListener:registerEvent("onUpdate")
checkEvents.events = {}
function checkEvents:onUpdate(elapsed)
	local x,y = player.body:pos()
	for id, event in pairs(self.events) do
		if event(x, y) then
			self.events[id] = nil
		end
	end
end

player = make:player()
player.xDir = 0
player.groundContacts = 0
player.body:setPos(0, 0)
player:register()
player.body:setGravityScale(0)
Graphics.setCamera(player.body)

function player.body:onContactBegin(other)
	if other.parent.isGround then
		self.parent.groundContacts = self.parent.groundContacts + 1
	end
end

function player.body:onContactEnd(other)
	if other.parent.isGround then
		self.parent.groundContacts = self.parent.groundContacts - 1
	end
end

local ControlState = {}
function ControlState:onKeyDown(key)
	if key == "w" and player.groundContacts > 0 then
		player.body:applyForceToCenter(0, 150)
	end
	if key == "a" then
		player.xDir = player.xDir -1
	end
	if key == "d" then
		player.xDir = player.xDir + 1
	end
end

function ControlState:onKeyUp(key)
	if key == "Escape" then
		--States.push(UI.MainMenu)
	end
	if key == "a" then
		player.xDir = player.xDir + 1
	end
	if key == "d" then
		player.xDir = player.xDir - 1
	end
end

local rooms = {}
function onPhysicsUpdate(timestep)
	player.body:applyForceToCenter(player.xDir * 3, 0)
	local x, y = player.body:linearVelocity()
	player.body:setLinearVelocity(math.clamp(x, -3, 3), y)

	local x, y = player.body:pos()
	if y < - 15 then
		player.body:setLinearVelocity(0, 0)
		player.body:setAngularVelocity(0)
		player.body:setPos(0, 0)
		player.body:setAngle(0)
	end
end

rooms.start = function(self)
	local cube1 = make:cube()
	cube1.body:setPos(3, 0)
	cube1:register()

	local cube2 = make:cube()
	cube2.body:setPos(-3, 0)
	cube2:register()

	local cube3 = make:cube()
	cube3.body:setPos(0, 1.5)
	cube3:register()

	local cube4 = make:cube()
	cube4.body:setPos(0, -1.5)
	cube4:register()

	fadeIn(cube1.renderable, 0.5, 1.0)
	fadeIn(player.renderable, 0.5, 2.5)
	fadeIn(cube2.renderable, 0.5, 4.0)
	fadeIn(cube3.renderable, 0.5, 5.5)
	fadeIn(cube4.renderable, 0.5, 5.5)

	timer.events[6] = function()
		player.body:setGravityScale(1)
		States.push(ControlState)
	end

	checkEvents.events.start = function(x, y)
		if y < 2 then
			return false
		end

		rooms.ladder()
		return true
	end
end

rooms.ladder = function()
	LibFx.New{
		frame = player.renderable,
		anim = "Color",
		duration = 5,
		r = 0, g = 0, b = 0, a = 1,
	}()

	for i =1, 3 do
		local cube = make:cube()
		cube.renderable:setColor(0, 0, 0, 0)
		cube.body:setPos(0, 1.5 + 2.2 * i)
		cube:register()
		fadeIn(cube.renderable, 5, (i-1) * 3)
	end

	failor = make:cube()
	failor.body:setType("dynamic")
	failor.renderable:setColor(0, 0, 0, 1)
	failor.body:setPos(3.5, 1.5 + 2.2 * 3)
	failor:register()
	failor.body:setGravityScale(0)

	function failor.body:onContactBegin(other)
		if other ~= player.body then
			return
		end
		self.onContactBegin = nil

		LibFx.New{
			frame = failor.renderable,
			anim = "Alpha",
			duration = 3,
			finish = 0,
			onComplete = function()
				rooms.transporter()
				failor:unregister()
				failor = nil
			end,
		}()
	end
end

rooms.transporter = function()
	local band = make(nil, { "Body", "Renderable" })
	band.body:setShape("box", 50, 0.05)
	band.body:setType("static")
	band.body:setPos(50, 8.1)
	band.isGround = true
	band.renderable:setPositionable(band.body)
	band.renderable:setShape("box", 100, 0.1)
	band.renderable:setColor(0, 0, 0, 1)
	band:register()

	function band.body:onContactBegin(other)
		if other ~= player.body then
			return
		end

		player.xDir = player.xDir + 5
	end

	function band.body:onContactEnd(other)
		if other ~= player.body then
			return
		end

		player.xDir = player.xDir - 5
	end

	math.randomseed(os.time())
	for i = 1, 40 do
		local bgFactor = 0.05 + math.random()*0.8
		local cube = make(nil, { "StaticPos", "Renderable" })
		cube.staticPos:setPos(math.random()*80, 5+math.random()*6)
		cube.renderable:setPositionable(cube.staticPos)
		local size = 0.01 + math.random()
		cube.renderable:setShape("box", size, size)
		cube.renderable:setColor((0.5+math.random()/2)*bgFactor,
		                         (0.5+math.random()/2)*bgFactor,
		                         (0.5+math.random()/2)*bgFactor,
								 0)
		cube.renderable:setParallax(bgFactor, bgFactor)
		cube.renderable:setZIndex(-bgFactor*0.9-0.1)
		cube:register()
		fadeIn(cube.renderable, 10)
	end

	checkEvents.events.loadIsland = function(x, y)
		if x < 80 then
			return false
		end

		rooms.island()
		return true
	end
end

function rooms.island()
	local arc = make(nil, { "StaticPos", "Renderable" })
	arc.staticPos:setPos(97, 5.1)
	arc.renderable:setPositionable(arc.staticPos)
	arc.renderable:setTexture("res/images/ground/island-arc.png")
	arc.renderable:setShape("box", 6, 6)
	arc:register()

	local island = make:cube()
	island.isGround = true
	island.body:setShape("box", 20, 3)
	island.body:setPos(119, 5.15)
	island.renderable:setShape("box", 40, 6)
	island.renderable:setColor(0, 0, 0, 1)
	island:register()

	for i = 0, 150 do
		local grass = make:background()
		grass.staticPos:setPos(90 + i*0.3, 8.3)
		grass.renderable:setShape("box", 0.77, 0.33)
		grass.renderable:setTexture("res/images/ground/grass"..math.random(1, 3)..".png")
		grass:register()
	end
end

player.body:setPos(100, 9)
rooms.start()
rooms.transporter()
