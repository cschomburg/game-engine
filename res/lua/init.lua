local frameCount, lastUpdate, fps = 0, 0, 0

local total = 0
function OnUpdate(elapsed)
	lastUpdate = lastUpdate + elapsed
	frameCount = frameCount + 1
	total = total + elapsed

	if lastUpdate > 1 then
		print(frameCount)
		lastUpdate = 0
		frameCount = 0
	end

	--Player:addVelocity(300 * elapsed, 0)
end

function Player:addVelocity(x, y)
	local oX, oY = self:velocity()
	self:setVelocity(oX + x, oY + y)
end

function Player:accelerate(x, y)
	local oX, oY = self:acceleration()
	self:setAcceleration(oX + x, oY + y)
end
