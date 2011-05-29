local frameCount, lastUpdate, fps = 0, 0, 0

function onUpdate(elapsed)
	lastUpdate = lastUpdate + elapsed
	frameCount = frameCount + 1

	if lastUpdate > 1 then
		print(frameCount)
		lastUpdate = 0
		frameCount = 0

		--player:setVelocity(0, 1000)
	end
end
