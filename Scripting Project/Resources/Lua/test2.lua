-- Test Script

enemy = nil

function callCFunc()
	print("Calling C/C++ function from Lua")
	--MemberFunction("TestLuaFunction1")
	MemberFunction("TestLuaFunction2", 1)
end
