
local moveInit = false

local enteredDoorUp = false;
local enteredDoorRight = false;
local enteredDoorDown = false;
local enteredDoorLeft = false;

function MovePlayer(direction, cellSize)

	local offsetX = 0.0
	local offsetY = 0.0
	if (direction == 0) then -- UP
		offsetY = -1.0
	elseif (direction == 1) then -- DOWN
		offsetY = 1.0
	elseif (direction == 2) then -- LEFT
		offsetX = -1.0
	elseif (direction == 3) then -- RIGHT
		offsetX = 1.0
	end

	local x = -1.0
	local y = -1.0
	local r = false

	if (GetDirection() == direction) then
		moveInit = true
		x = GetPosX() + cellSize * offsetX
		y = GetPosY() + cellSize * offsetY
		r = true
	else
		SetDirection(direction)
	end
	
	return x, y, r
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

	if (GetPosX() == 1 * cellSize) then
		enteredDoorLeft = true
	end
	if (GetPosY() == 1 * cellSize) then
		enteredDoorUp = true
	end

	if (GetPosX() == cellSize * (worldWidth - 2)) then
		enteredDoorRight = true
	end
	if (GetPosY() == cellSize * (worldHeight - 2)) then
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