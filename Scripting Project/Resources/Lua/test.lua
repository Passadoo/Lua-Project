-- Test Script

enemy = nil

function init()
	print("Calling C/C++ function from Lua")
	enemy = Test.new()
end

function setPos(x, y)
	enemy:setPos(x, y)
end
