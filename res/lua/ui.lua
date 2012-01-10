local text = TextWidget.new("Text")
text:setParent(UI.root())
text:setPos(-1024/2, -576/2 + 10)
text:setColor(1, 0.8, 0.5, 1)
text:setFont("res/font.ttf", 10)
text:setText("Game 0.0.1 Pre-Alpha Unreleased Debug Test Version in Development")

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
