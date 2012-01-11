function string:capitalize()
	return self:sub(1,1):upper()..self:sub(2)
end

function string:lowercap()
	return self:sub(1,1):lower()..self:sub(2)
end

function math.clamp(value, min, max)
	return math.min(math.max(value, min), max)
end

function call(obj, func, ...)
	if obj and obj[func] then return obj[func](obj, ...) end
end
