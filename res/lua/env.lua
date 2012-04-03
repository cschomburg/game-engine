function optrequire(...)
	local success, lib = pcall(require, ...)
	if(success) then return lib end
end

function string:uppercap()
	return self:sub(1,1):upper()..self:sub(2)
end

function string:lowercap()
	return self:sub(1,1):lower()..self:sub(2)
end

function string:islowercap()
	local l = self:sub(1,1)
	return l == l:lower()
end

function math.clamp(val, min, max)
	return math.min(math.max(val, min), max)
end

function call(obj, func, ...)
	if obj and obj[func] then return obj[func](obj, ...) end
end

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
