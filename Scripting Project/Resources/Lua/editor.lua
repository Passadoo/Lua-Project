
local toCreate = 0

function decrementToCreate(starting, ending)
	toCreate = toCreate - 1
	if (toCreate < starting) then
		toCreate = ending - 1
	end
end

function incrementToCreate(starting, ending)
	toCreate = toCreate + 1
	if (toCreate >= ending) then
		toCreate = starting
	end
end

function GetToCreate()
	return toCreate
end

function Update(ptr, a, b, c)
	print("called Update")
	--print(ptr + " " + a + " " + b + " " + c)
	--ptr::func();
	ret = MemberFunction2("TestLuaFunction6", 2, 3);
	--print(ret)
	--if (ret == true) then
	--	print("returned true")
	--elseif
	--	print("returned false")
	--end
	return 10
end