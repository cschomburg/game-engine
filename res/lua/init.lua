math.randomseed(os.time())

for _,file in pairs{
	"debug",
	"make",
	"events",
	"util",
	"game",
} do
	assert(loadfile("res/lua/"..file..".lua"))()
end
