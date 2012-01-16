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

--[[
local text = TextWidget.new("Text")
text:setParent(UI.root())
text:setPos(-1024/2, -576/2 + 10)
text:setColor(1, 0.8, 0.5, 1)
text:setFont("res/font.ttf", 10)
text:setText("Game 0.0.1 Pre-Alpha Unreleased Debug Test Version in Development")
]]

local fps = make("FPS", { "TextWidget", "EventListener" })
fps.eventListener:registerEvent("onUpdate")
fps.textWidget:setParent(UI.root())
fps.textWidget:setPos(1024/2 - 150, -576/2 + 14)
fps.textWidget:setColor(1, 0.8, 0.5, 1)
fps.textWidget:setFont("res/font.ttf", 18)
fps.textWidget:setText("FPS")

function fps:onUpdate(elapsed)
	self.lastUpdate = (self.lastUpdate or 0) + elapsed
	self.frameCount = (self.frameCount or 0) + 1

	if self.lastUpdate > 1 then
		self.textWidget:setText("FPS: "..self.frameCount)
		print(self.frameCount)
		self.lastUpdate = 0
		self.frameCount = 0
	end
end
