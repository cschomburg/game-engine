local console = {}
UI.Console = console

local _print = print
function print(...)
	_print(...)
	local msg = ""
	for i=1, select('#', ...) do
		if msg ~= "" then msg = msg.." " end
		msg = msg..tostring(select(i, ...))
	end
	if msg == "" then return end
	console:addMessage(msg)
end

function console:onKeyDown(key, char)
	if key == "`" then
		States.pop()
	elseif key == "Escape" then
		console:clearInput()
	elseif key == "Backspace" then
		console:deleteChar()
	elseif key == "Return" then
		console:process()
	else
		console:addChar(char)
	end
	return true
end

function console:onKeyUp(key)
	return true
end

function console:init()
	local bg = SolidWidget.new("Console")
	bg:setShown(false)
	bg:setParent(UI.root())
	bg:setColor(0, 0, 0, 0.8)
	bg:setRect(-1024/2, -576/2, 1024, 576)
	self.bg = bg

	self.messages = {}
	self.lines = {}
	for i = 1, 21 do
		local line = TextWidget.new("ConsoleLine"..i)
		line:setParent(bg)
		line:setColor(1, 1, 1, 1)
		line:setFont("res/font.ttf", 12)
		line:setPos(-1024/2+30, 576/2 - 10 - i*24)
		self.lines[i] = line
	end

	local edit = TextWidget.new("ConsoleInput")
	edit:setParent(bg)
	edit:setColor(1, 1, 1, 1)
	edit:setFont("res/font.ttf", 12)
	edit:setPos(-1024/2+30, -576/2 + 20)
	self.edit = edit

	self.input = ""
	self:updateText()
end

function console:addMessage(msg)
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

function console:onEnter()
	if console.init then
		console:init()
		console.init = nil
	end
	self.bg:setShown(true)
end

function console:onLeave()
	self.bg:setShown(false)
end

function console:clearInput()
	self.input = ""
	self:updateText()
end

function console:addChar(char)
	self.input = self.input..char
	self:updateText()
end

function console:deleteChar()
	if self.input == "" then return end
	self.input = self.input:sub(1, #self.input-1)
	self:updateText()
end

function console:updateText()
	self.edit:setText("> "..self.input)
end

function console:process()
	if self.input == "" then return end
	console:addMessage("> "..self.input)
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

function console:redraw()
	if not self.lines then return end
	for i, line in pairs(self.lines) do
		line:setText(self.messages[i] or "")
	end
end
