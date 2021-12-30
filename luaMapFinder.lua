local mapSearch = require "mapSearch"
local luaMapFinder = class("luaMapFinder")

function luaMapFinder:ctor()
	self.super.ctor(self)
	
	self.obj = mapSearch()
end

function luaMapFinder:testFun(a, b)
	return self.obj:testFun(a, b)
end

return luaMapFinder

