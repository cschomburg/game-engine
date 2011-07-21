function properties()
	return {
		['size'] = { 2000, 1500 },
		['spawn'] = { 572, 456 },
		['gravitation'] = { 0, -800 },
		['background'] = {
			['colorA'] = { 255, 89, 0 },
			['colorB'] = { 180, 20, 0 },
		},
	}
end

function objects()
	return {
		['player'] = {
			['Positionable'] = properties()['spawn'],
			['Shape'] = { 32, 32 },
			['Movable'] = true,
			['Walkable'] = 500,
			['Renderable'] = "res/images/foo.png",
		},
		['camera'] = {
			['Positionable'] = true,
			['Tracker'] = true,
		},

		{
			['Positionable'] = { 512, 587},
			['Shape'] = { 512, 512 },
			['Renderable'] = "res/images/sun.png",
		},
	}
end
