--[[
    寻路
    eg:
        local luaMapSearch = require("cpp.luaMapSearch")
        local ms = luaMapSearch.new()
        ms:init(1, 1215)
        local path = ms:findPath(0, 0, 1215-1, 1215-1)
]]
local mapSearch = require "mapSearch"

local mt = {}
mt.__index = mt

function mt:testFun(a, b)
    return self.ms:testFun(a, b)
end

-- 初始化
function mt:init(mapType, mapSize, mapFile)
    return self.ms:init(mapType, mapSize, mapFile)
end

-- 寻路
function mt:findPath(x1, y1, x2, y2)
    return self.ms:findPath(x1, y1, x2, y2)
end

local M = {}
function M.new()
    local obj = {}
    obj.ms = mapSearch()
    return setmetatable(obj, mt)
end

return M

