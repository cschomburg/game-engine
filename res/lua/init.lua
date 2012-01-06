for _,file in pairs{
	"debug",
	"make",
} do
	assert(loadfile("res/lua/"..file..".lua"))()
end

function string:capitalize()
	return self:sub(1,1):upper()..self:sub(2)
end

function string:lowercap()
	return self:sub(1,1):lower()..self:sub(2)
end

--[[--------------
	Other stuff
-----------------]]

local frameCount, lastUpdate, fps = 0, 0, 0

local total = 0
function onUpdate(elapsed)
	lastUpdate = lastUpdate + elapsed
	frameCount = frameCount + 1
	total = total + elapsed

	if lastUpdate > 1 then
		print(frameCount)
		lastUpdate = 0
		frameCount = 0
	end
end

function onQuit()
	print ("Bye!")
end

math.randomseed(os.time())
