local Events = require("base.events")
local Game = require("game.main")
local make = require("base.make").make

local UI = {}

--[[
local mainMenu = {}
UI.MainMenu = mainMenu

function mainMenu:init()
	local bg = SolidWidget.new("MainMenuBackground")
	bg:setShown(false)
	bg:setParent(UI.root())
	bg:setColor(0, 0, 0, 0)
	bg:setRect(-1024/2, -576/2, 1024, 576)
	self.bg = bg

	bg.fadeIn = LibFx.New{
		frame = bg,
		anim = "Alpha",
		finish = 0.8,
		duration = 0.2,
		onStart = function() bg:setShown(true) end,
	}
	bg.fadeOut = LibFx.New{
		frame = bg,
		anim = "Alpha",
		finish = 0,
		onComplete = function() bg:setShown() end,
		duration = 0.2,
	}

	local nav = Widget.new("MainMenuNav")
	nav:setParent(bg)
	nav.selected = 1;
	self.nav = nav
	for i, label in ipairs{ "Start", "Options", "Configuration", "Lulz" } do
		local widget = TextWidget.new("MainMenu"..label)
		widget:setParent(bg)
		widget:setColor(1, 1, 1, 1)
		widget:setFont("res/font.ttf", 18)
		widget:setPos(-1024/2+50, 576/2 - 100 - i*26)
		widget:setText(label)
		self.nav[i] = widget
	end
end

function mainMenu:onEnter()
	self.bg.fadeIn()
end

function mainMenu:onLeave()
	self.bg.fadeOut()
end

function mainMenu:onKeyUp(key)
	if key == "Escape" or key == " " then
		States.pop()
	end
end
mainMenu:init()
]]

local fps = make{
	StaticPos = {pos={1024/2 - 150, -576/2 + 14}},
	FontRenderable = {
		drawLayer = "foreground",
		positionable = "$.StaticPos",
		color = {1, 0.8, 0.5, 1},
		font = {"res/font.ttf", 18},
		text = "FPS",
		boundingRect = {1,1},
	},
}
Game.register(fps)
Events.register("onUpdate", fps)

function fps:onUpdate(elapsed)
	self.lastUpdate = (self.lastUpdate or 0) + elapsed
	self.frameCount = (self.frameCount or 0) + 1

	if self.lastUpdate > 1 then
		--print(self.frameCount)
		self.FontRenderable:setText("FPS: "..self.frameCount)
		self.lastUpdate = 0
		self.frameCount = 0
	end
end
Events.register("onUpdate", fps)

return UI
