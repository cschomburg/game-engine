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
end
