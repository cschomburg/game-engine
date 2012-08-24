local Events = require("base.events")
local make = require("base.make").newMake
local Level = require("game.level")
local EventListener = require("components.eventlistener")

local level = Level.new()
level.comp = {}

-- Background {{{
do local o = make{TextureRenderable}
	level.comp.Background = o
	do local r = o.comp.TextureRenderable
		r:setDrawLayer("background")
		r:setBoundingRect(1024, 1024)
		r:setTexture("res/images/background/tile-1.png")
		--r:setColor(159/255, 96/255, 65/255, 1)
		r:setZIndex(-3)
	end
end -- }}}

-- Noise {{{
do local o = make{TextureRenderable}
	level.comp.Noise = o
	do local r = o.comp.TextureRenderable
		r:setBoundingRect(20.24, 20.24)
		r:setTexture("res/images/effects/noise.png")
		--r:setColor(159/255, 96/255, 65/255, 1)
		r:setParallax(1, 1)
		r:setZIndex(3)
		r:setColor(1, 1, 1, 0.2)
	end
end -- }}}

-- Sun {{{
do local o = make{TextureRenderable}
	level.comp.Sun = o
	do local r = o.comp.TextureRenderable
		r:setBoundingRect(10.24, 10.24)
		r:setBlendMode("add")
		r:setTexture("res/images/background/sun1.png")
		r:setParallax(0.99, 0.99)
		r:setZIndex(-2)
	end
end -- }}}

-- Cloud1 {{{
do local o = make{TextureRenderable}
	level.comp.Cloud1 = o
	do local r = o.comp.TextureRenderable
		r:setPos(0, -28)
		r:setBoundingRect(9.47, 3.65)
		r:setTexture("res/images/clouds/layer1.png")
		r:setParallax(0.9, 0.9)
		r:setZIndex(-1)
	end
end -- }}}

-- Cloud2 {{{
do local o = make{TextureRenderable}
	level.comp.Cloud2 = o
	do local r = o.comp.TextureRenderable
		r:setPos(18, 14)
		r:setBoundingRect(3.71, 3.13)
		r:setTexture("res/images/clouds/single1.png")
		r:setParallax(0.8, 0.8)
		r:setZIndex(-1)
	end
end -- }}}

-- Island {{{
do local o = make{Body, TextureRenderable}
	level.comp.Island = o
	do local b = o.comp.Body
		b:setPos(0, 0)
		b:setType("static")
		b:setShape("box", 1, 0.64)
	end
	do local r = o.comp.TextureRenderable
		r:setAnchor(o.comp.Body)
		r:setBoundingRect(2.02, 1.4)
		r:setTexture("res/images/island.png")
	end
end -- }}}

-- Tree {{{
do local o = make{TextureRenderable}
	level.comp.Tree = o
	do local r = o.comp.TextureRenderable
		r:setPos(0, 1.3)
		r:setBoundingRect(2.23*3/5, 2.26*3/5)
		r:setTexture("res/images/background/tree2.png")
		r:setZIndex(1)
	end
end -- }}}

-- Gear01 {{{
do local o = make{TextureRenderable, EventListener}
	level.comp.Gear01 = o
	o.comp.EventListener:listen{"onPhysicsUpdate"}
	do local r = o.comp.TextureRenderable
		r:setPos(-0.9, 0.6)
		r:setBoundingRect(1, 1)
		r:setTexture("res/images/gears/mid03.png")
	end

	function o:onPhysicsUpdate(dt)
		local angle = self.comp.TextureRenderable:angle()
		self.comp.TextureRenderable:setAngle(angle - dt/2)
	end
end -- }}}

-- Gear02 {{{
do local o = make{Body, TextureRenderable}
	level.comp.Gear02 = o
	do local b = o.comp.Body
		b:setPos(0.5, 2)
		b:setType("dynamic")
		b:setShape("circle", 0.25)
	end
	do local r = o.comp.TextureRenderable
		r:setAnchor(o.comp.Body)
		r:setBoundingRect(0.5, 0.5)
		r:setTexture("res/images/gears/mid03.png")
	end
end -- }}}

print("loaded")

return level
