local Level = require("game.level")

local level = Level.new()
level:load{
	Background = {
		StaticPos = true,
		TextureRenderable = {
			positionable = "$.StaticPos",
			boundingRect = {10.24, 10.24},
			texture = D.img("background/tile-1.png"),
			--color = { 159/255, 96/255, 65/255, 1 },
			parallax = {1, 1},
		},
	},
	Noise = {
		StaticPos = true,
		TextureRenderable = {
			positionable = "$.StaticPos",
			boundingRect = {20.24, 20.24},
			texture = D.img("effects/noise.png"),
			parallax = {1, 1},
			zIndex = 1,
			color = {1, 1, 1, 0.2},
		},
	},
	Sun = {
		StaticPos = true,
		TextureRenderable = {
			positionable = "$.StaticPos",
			boundingRect = {10.24, 10.24},
			blendMode = "add",
			texture = D.img("background/sun1.png"),
			parallax = {0.99, 0.99},
		},
	},
	--[[SunEffect = {
		StaticPos = true,
		TextureRenderable = {
			positionable = "$.StaticPos",
			boundingRect = {2, 2},
			blendMode = "add",
			texture = D.img("sun.png"),
			parallax = {0.9, 0.9},
			color = {1, 1, 1, 0.2},
			zIndex = 1,
		},
	},]]
	Cloud1 = {
		StaticPos = {pos = {0, -28}},
		TextureRenderable = {
			positionable = "$.StaticPos",
			boundingRect = {9.47, 3.65},
			texture = D.img("clouds/layer1.png"),
			parallax = {0.9, 0.9},
		},
	},
	Cloud2 = {
		StaticPos = {pos = {18, 14}},
		TextureRenderable = {
			positionable = "$.StaticPos",
			boundingRect = {3.71, 3.13},
			texture = D.img("clouds/single1.png"),
			parallax = {0.8, 0.8},
		},
	},
	Island = {
		Body = {
			type = "static",
			shape = {"box", 1, 0.64},
		},
		TextureRenderable = {
			positionable = "$.Body",
			boundingRect = {2.02, 1.4},
			texture = D.img("island.png"),
		},
	},
	Tree = {
		StaticPos = {pos = {0, 1.3}},
		TextureRenderable = {
			positionable = "$.StaticPos",
			boundingRect = {2.23*3/5, 2.26*3/5},
			texture = D.img("background/tree2.png"),
		},
	},
	Player = {
		Body = {
			pos = {0, 1},
			shape = {"box", 0.1, 0.25},
		},
		SolidRenderable = {
			positionable = "$.Body",
			boundingRect = {0.24, 0.54},
			color = {0, 0, 0, 1},
		},
	},
}

return level
