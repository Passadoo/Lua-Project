
function UpdatePlayer(cellSize, worldWidth, worldHeight)
	local x = 0
	local y = 0
	local ret = false
	if (IsKeyPressed("D")) then
		x, y, ret = MovePlayer(3, cellSize) -- Right
	end
	
	if (IsKeyPressed("S")) then
		x, y, ret = MovePlayer(1, cellSize) -- Down
	end
	
	if (IsKeyPressed("A")) then
		x, y, ret = MovePlayer(2, cellSize) -- Left
	end
	
	if (IsKeyPressed("W")) then
		x, y, ret = MovePlayer(0, cellSize) -- Up
	end

	if (ret == true) then
		if (not NoDoor(x, y)) then
			print("entered door")
			UpdatePlayerInRoom(x, y, cellSize, worldWidth, worldHeight)
		elseif (NoObstacle(x, y)) then
			SetPosition(x, y)
		end
	end
end

function UpdatePlayerInRoom(x, y, cellSize, worldWidth, worldHeight)
	local enteredDoorUp = false;
	local enteredDoorRight = false;
	local enteredDoorDown = false;
	local enteredDoorLeft = false;
	enteredDoorUp, enteredDoorRight, enteredDoorDown, enteredDoorLeft = EnterRoom(cellSize, worldWidth, worldHeight)

	if (enteredDoorUp == true) then
		if (not RoomUpExists()) then
			if (AddRoomUp()) then
				LoadCurrentRoom()
				SetPlayerBeforeDoor(-1, cellSize * (worldHeight - 1), cellSize)
			else
				print("No more rooms exist in this direction")
			end
		else
			if (UpRoomHasDownDoor()) then
				SwitchRoomUp()
				SetPlayerBeforeDoor(-1, cellSize * (worldHeight - 1), cellSize)
			else
				print("A room exists but it does not have the required door")
			end
		end
	end

	if (enteredDoorRight == true) then
		if (not RoomRightExists()) then
			if (AddRoomRight()) then
				LoadCurrentRoom()
				SetPlayerBeforeDoor(0, -1, cellSize)
			else
				print("No more rooms exist in this direction")
			end
		else
			if (RightRoomHasLeftDoor()) then
				SwitchRoomRight()
				SetPlayerBeforeDoor(0, -1, cellSize)
			else
				print("A room exists but it does not have the required door")
			end
		end
	end

	if (enteredDoorDown == true) then
		if (not RoomDownExists()) then
			if (AddRoomDown()) then
				LoadCurrentRoom()
				SetPlayerBeforeDoor(-1, 0, cellSize)
			else
				print("No more rooms exist in this direction")
			end
		else
			if (DownRoomHasUpDoor()) then
				SwitchRoomDown()
				SetPlayerBeforeDoor(-1, 0, cellSize)
			else
				print("A room exists but it does not have the required door")
			end
		end
	end


	if (enteredDoorLeft == true) then
		if (not RoomLeftExists()) then
			if (AddRoomLeft()) then
				LoadCurrentRoom()
				SetPlayerBeforeDoor(cellSize * (worldWidth - 1), -1, cellSize)
			else
				print("No more rooms exist in this direction")
			end
		else
			if (LeftRoomHasRightDoor()) then
				SwitchRoomLeft()
				SetPlayerBeforeDoor(cellSize * (worldWidth - 1), -1, cellSize)
			else
				print("A room exists but it does not have the required door")
			end
		end
	end

	print("There are " .. GetNrOfRemainingRooms() .. " rooms remaining")
end

function SetPlayerBeforeDoor(x, y, cellSize)
	if (x == -1) then
		newX = GetXDoorY(y)
		if (newX >= 0) then
			if (y == 0) then
				SetPosition(newX, y + cellSize)
			else
				SetPosition(newX, y - cellSize)
			end
		end
	elseif (y == -1) then
		newY = GetYDoorX(x)
		if (newY >= 0) then
			if (x == 0) then
				SetPosition(x + cellSize, newY)
			else
				SetPosition(x - cellSize, newY)
			end
		end
	end
end

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
		x = GetPosX() + cellSize * offsetX
		y = GetPosY() + cellSize * offsetY
		r = true
	else
		SetDirection(direction)
	end
	
	return x, y, r
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
	
	return enteredDoorUp, enteredDoorRight, enteredDoorDown, enteredDoorLeft
end