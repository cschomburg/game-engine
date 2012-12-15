-- Package selector enables simple multi-table traversing by specifing a path
-- string to follow.
--
-- Example:
--     local tbl = {}
--     Selector.set(tbl, "deep.below.var", 25)
--         => tbl == { deep = { below = { var = 25 }}},
--     Selector.get(tbl, "deep.below.var")
--         => returns: 25
--
local Selector = {}

-- Get returns the value of the table 'ref' along the path 'str'.
-- If no value was found, 'fallback' is returned.
function Selector.get(ref, str, fallback)
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

-- Set stores the value in the table 'ref' along the path 'str'.
-- If the optional 'noforce' is set, no new sub-tables will be created and
-- the function fails silently.
function Selector.set(ref, str, val, noforce)
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

return Selector
