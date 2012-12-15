-- Package Store provides a simple nested key-value store.
local Store = {}

local Selector = require("base.selector")

local mt = {__index = Store}

Store.get = Selector.get
Store.set = Selector.set

-- Creates a new store, optionally saved in the parent store under path 'key'.
-- If 'store' already contains a table, it will be converted to a store.
function Store:new(key, store)
	store = store or {}
	setmetatable(store, mt)
	if key then
		self:set(key, store)
	end
	return store
end

-- Returns a child store from 'key', creating one if necessary.
function Store:store(key)
	return self:get(key) or self:new(key)
end

return Store
