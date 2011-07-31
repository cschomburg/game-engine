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

function dump(o)
	local found = {}
	local function dump_r(o)
		if type(o) == 'table' and not found[o] then
			found[o] = true
			local s = '{ '
			for k,v in pairs(o) do
				if type(k) ~= 'number' then k = '"'..k..'"' end
				s = s .. '['..k..'] = ' .. dump_r(v) .. ','
			end
			return s .. '} '
		else
			return tostring(o)
		end
	end
	print(dump_r(o))
end

player.test = true

dump(player)
dump(player:component("Positionable"):object())
dump(player == player:component("Positionable"):object())
