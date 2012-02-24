local Selector = {}

local function selector(ref, str)
	for w in str:gmatch("[^%.]+") do
		if w == "$" then
			ref = ref.parent
		elseif ref[w] then
			ref = ref[w]
		end
		if not ref then return end
	end
	return ref
end
Selector.selector = selector

function Selector.mixin(self)
	self.selector = selector
end

return Selector
