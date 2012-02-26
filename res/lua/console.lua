local States = require("states")
local Console = {}

local _print = print
function print(...)
	_print(...)
	local msg = ""
	for i=1, select('#', ...) do
		if msg ~= "" then msg = msg.." " end
		msg = msg..tostring(select(i, ...))
	end
	if msg == "" then return end
	Console:addMessage(msg)
end

function Console:onKeyDown(key, char)
	if key == "`" then
		States.pop()
	elseif key == "escape" then
		Console:clearInput()
	elseif key == "backspace" then
		Console:deleteChar()
	elseif key == "return" then
		Console:process()
	else
		Console:addChar(char)
	end
	return true
end

function Console:onKeyUp(key)
	return true
end

function Console:init()
	local z = 90

	local bg = SolidRenderable.new()
	do local pos = StaticPos.new()
		pos:setPos(0, 0)
		bg:setPositionable(pos)
	end
	bg:setDrawLayer("foreground")
	bg:setZIndex(z)
	bg:setColor(0, 0, 0, 0.8)
	bg:setBoundingRect(1024, 576)
	self.bg = bg

	self.messages = {}
	self.lines = {}
	for i = 1, 21 do
		local line = FontRenderable.new()
		line:setDrawLayer("foreground")
		line:setZIndex(z+1)
		line:setColor(1, 1, 1, 1)
		line:setFont("res/font.ttf", 12)
		do local pos = StaticPos.new()
			pos:setPos(-1024/2+30, 576/2 - 10 - i*24)
			line:setPositionable(pos)
		end
		self.lines[i] = line
	end

	local edit = FontRenderable.new()
	edit:setDrawLayer("foreground")
	edit:setZIndex(z+1)
	edit:setColor(1, 1, 1, 1)
	edit:setFont("res/font.ttf", 12)
	do local pos = StaticPos.new()
		pos:setPos(-1024/2+30, -576/2 + 20)
		edit:setPositionable(pos)
	end
	self.edit = edit

	self.input = ""
	self:updateText()
end

function Console:addMessage(msg)
	if not msg or msg == "" then return end
	if msg:find("\r?\n") then
		for line in msg:gmatch("[^\r\n]+") do
			self:addMessage(line)
		end
		return
	end

	msg = msg:gsub("\t", "    ")
	self.messages = self.messages or {}
	self.messages[#self.messages+1] = msg
	while #self.messages > 21 do
		table.remove(self.messages, 1)
	end
	self:redraw()
end

function Console:onEnter()
	if self.init then
		self:init()
		self.init = nil
	end

	self.bg:register()
	for _, line in pairs(self.lines) do
		line:register()
	end
	self.edit:register()
end

function Console:onLeave()
	self.bg:unregister()
	for _, line in pairs(self.lines) do
		line:unregister()
	end
	self.edit:unregister()
end

function Console:clearInput()
	self.input = ""
	self:updateText()
end

function Console:addChar(char)
	self.input = self.input..char
	self:updateText()
end

function Console:deleteChar()
	if self.input == "" then return end
	self.input = self.input:sub(1, #self.input-1)
	self:updateText()
end

function Console:updateText()
	self.edit:setText("> "..self.input)
end

function Console:process()
	if self.input == "" then return end
	Console:addMessage("> "..self.input)
	local func, err = loadstring(self.input)
	if err then
		return print(err)
	end
	local ret = {pcall(func)}
	local success = table.remove(ret, 1)
	print(unpack(ret))
	if success then
		self:clearInput()
	end
end

function Console:redraw()
	if not self.lines then return end
	for i, line in pairs(self.lines) do
		line:setText(self.messages[i] or "")
	end
end

return Console
