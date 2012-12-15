-- Package Persistence saves and loads Lua values in the file system.
--
-- Example:
--     Persistence.save("/tmp/session", "hello!", 5, {a = "nope"})
--     local str, num, tbl = Persistence.load("/tmp/session")
--
local Persistence = {}

local write, writeIndent, writers, refCount

-- Persistence.store saves multiple arguments at the specified file path.
function Persistence.store(path, ...)
	local n = select("#", ...)
	if n == 0 then return end
	local file, e = io.open(path, "w")
	if not file then
		return error(e)
	end
	file:write("return ")
	for i = 1, n do
		if i > 1 then file:write(", ") end
		write(file, (select(i,...)), 0, objRefNames)
	end
	file:close()
end

-- Persistence.load returns multiple variables saved at the specified file path.
function Persistence.load(path)
	local f, e = loadfile(path)
	if not f then
		return nil, e
	end
	return f()
end

-- write thing (dispatcher)
write = function (file, item, level)
	writers[type(item)](file, item, level)
end

-- write indent
writeIndent = function (file, level)
	for i = 1, level do
		file:write("\t")
	end
end

-- Format items for the purpose of restoring
writers = {
	["nil"] = function (file, item)
		file:write("nil")
	end,
	["number"] = function (file, item)
		file:write(tostring(item))
	end,
	["string"] = function (file, item)
		file:write(string.format("%q", item))
	end,
	["boolean"] = function (file, item)
		file:write(item and "true" or "false")
	end,
	["table"] = function (file, item, level)
		file:write("{\n")
		for k, v in pairs(item) do
			writeIndent(file, level+1)
			file:write("[")
			write(file, k, level+1)
			file:write("] = ")
			write(file, v, level+1)
			file:write(",\n")
		end
		writeIndent(file, level)
		file:write("}")
	end,
	["function"] = function (file, item)
		local dInfo = debug.getinfo(item, "uS")
		if dInfo.nups > 0 then
			file:write("nil --[[functions with upvalue not supported]]")
		elseif dInfo.what ~= "Lua" then
			file:write("nil --[[non-lua function not supported]]")
		else
			local r, s = pcall(string.dump,item)
			if r then
				file:write(string.format("loadstring(%q)", s))
			else
				file:write("nil --[[function could not be dumped]]")
			end
		end
	end,
	["thread"] = function (file, item)
		file:write("nil --[[thread]]")
	end,
	["userdata"] = function (file, item)
		file:write("nil --[[userdata]]")
	end,
}

return Persistence
