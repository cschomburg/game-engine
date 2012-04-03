package.path = "./res/lua/?.lua;"..package.path
math.randomseed(os.time())
require("env")

local Events = require("base.events")
local Game = require("game.main")
local States = require("game.states")
local ControlState = require("game.states.control")
local Player = require("entities.player")
local UI = require("ui.main")
local FileWatcher = require("debug.filewatcher")

local make = require("base.make").make

Events.call("onInit")

local level
FileWatcher.watch("res/lua/levels/01.lua", function(file)
	local f, err = loadfile(file)
	if not f then return print(err) end

	local success, value = pcall(f)
	if not success then return print(value) end

	if level then Game.unregister(level) end
	level = value
	Game.register(level)
end)

player = Player.new()
Game.register(player)
Graphics.setCamera(player.comp.Body)
ControlState.player = player
States.push(ControlState)
