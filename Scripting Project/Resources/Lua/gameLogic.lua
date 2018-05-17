
local moveInit = false

local enteredDoorUp = false;
local enteredDoorRight = false;
local enteredDoorDown = false;
local enteredDoorLeft = false;

function MovePlayer(direction, cellSize)

	local offsetX = 0
	local offsetY = 0
	if (direction == 0) then -- UP
		offsetY = -1
	elseif (direction == 1) then -- DOWN
		offsetY = 1
	elseif (direction == 2) then -- LEFT
		offsetX = -1
	elseif (direction == 3) then -- RIGHT
		offsetX = 1
	end

	if (MemberFunction("GetDirection", 1) == direction) then
		moveInit = true
		return true, MemberFunction("GetPosX", 2) + cellSize * offsetX, MemberFunction("GetPosY", 2) + cellSize * offsetY
	else
		MemberFunction("SetDirection", direction, 0)
		return false, -1, -1
	end
end

function SetMoveInitFalse()
	moveInit = false
end

function GetMoveInit()
	return moveInit
end

function EnterRoom(cellSize, worldWidth, worldHeight)

	enteredDoorUp = false;
	enteredDoorRight = false;
	enteredDoorDown = false;
	enteredDoorLeft = false;

	if (MemberFunction("GetPosX", 2) == 1 * cellSize) then
		enteredDoorLeft = true
	end
	if (MemberFunction("GetPosY", 2) == 1 * cellSize) then
		enteredDoorUp = true
	end

	if (MemberFunction("GetPosX", 2) == cellSize * (worldWidth - 2)) then
		enteredDoorRight = true
	end
	if (MemberFunction("GetPosY", 2) == cellSize * (worldHeight - 2)) then
		enteredDoorDown = true
	end
	
end

function GetEnteredDoorUp()
	return enteredDoorUp
end

function GetEnteredDoorDown()
	return enteredDoorDown
end

function GetEnteredDoorLeft()
	return enteredDoorLeft
end

function GetEnteredDoorRight()
	return enteredDoorRight
end