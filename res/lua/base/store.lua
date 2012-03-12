local Selector = require("base.selector")

local Store = {}
local mt = {__index = Store}

Store.get = Selector.get
Store.set = Selector.set

function Store:new(key, store)
	store = store or {}
	setmetatable(store, mt)
	if key then
		self:set(key, store)
	end
	return store
end

function Store:store(key)
	return self:get(key) or self:new(key)
end

return Store
