
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