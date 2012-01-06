function dump(...)
	local found = {}
	local function dump_r(o)
		if type(o) == 'table' and not found[o] then
			found[o] = true
			local s = '{\n'
			for k,v in pairs(o) do
				if type(k) ~= 'number' then k = '"'..tostring(k)..'"' end
				s = s .. '\t['..k..'] = ' .. dump_r(v):gsub("\n", "\n\t") .. ','
				s = s.."\n"
			end
			return s .. '} '
		else
			return tostring(o)
		end
	end

	local str = ""
	for i=1, select('#', ...) do
		if str ~= "" then str = str .. ", " end
		str = str .. dump_r(select(i, ...))
	end
	print(str)
end
