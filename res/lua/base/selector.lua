local Selector = {}

local function get(ref, str, fallback)
	for w in str:gmatch("[^%.]+") do
		if not ref then return fallback end
		if w == "$" then
			ref = ref.parent
		else
			ref = ref[w]
		end
	end
	if ref == nil then
		return fallback
	end
	return ref
end

local function set(ref, str, val, noforce)
	local lastRef, lastW
	for w in str:gmatch("[^%.]+") do
		if not ref then
			if noforce or not lastRef then return end
			ref = {}
			rawset(lastRef, lastW, ref)
		end
		lastRef, lastW = ref, w
		if w == "$" then
			ref = ref.parent
		else
			ref = ref[w]
		end
	end
	rawset(lastRef, lastW, val)
end

Selector.get = get
Selector.set = set

function Selector.mixin(self)
	self.get = get
	self.set = set
end

return Selector
