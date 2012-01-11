math.randomseed(os.time())

for _,file in pairs{
	"debug",
	"make",
	"events",
	"util",
	"states",

	"LibFx-1.1",

	"game",
	"ui",
} do
	assert(loadfile("res/lua/"..file..".lua"))()
end
