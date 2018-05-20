-- Set seed for random values
math.randomseed(os.time())

function UpdateEnemy(ptr, ptrL, cellSize, deltaTime)
	local newTime = ptr:GetEnemyFloat(ptrL, "GetTime") + deltaTime
	ptr:SetEnemyFloat(newTime, ptrL, "SetTime")

	-- Only move the enemy if the time of the enemies last movement is over 2
	if (newTime > 2) then
		ProcessMovement(ptr, ptrL, cellSize)
		ptr:SetEnemyFloat(0, ptrL, "SetTime")
		return
	end
end

function ProcessMovement(ptr, ptrL, cellSize)
	local direction = math.floor(math.random() * 100) % 4
	local startDir = direction

	-- Move the enemy to a emty place always so it do not stand still
	local moved = false
	repeat
		moved = Move(ptr, ptrL, cellSize, direction);

		-- If the enemy have tried to move to all directions but failed, go out of the loop
		if (moved == false) then
			direction = (direction + 1) % 4
			if (direction == startDir) then
				moved = true
			end
		end
	until( moved )
end

-- Move the enemy to a emtyp cell, if failed returns false
function Move(ptr, ptrL, cellSize, direction)
	local x = ptr:GetEnemyFloat(ptrL, "GetPosX")
	local y = ptr:GetEnemyFloat(ptrL, "GetPosY")

	if (direction == 0) then		--  UP   --
		return MoveEnemy(ptr, ptrL, direction, x, y - cellSize);
	elseif (direction == 1) then	-- Down  --
		return MoveEnemy(ptr, ptrL, direction, x, y + cellSize);
	elseif(direction == 2) then		-- Left  --
		return MoveEnemy(ptr, ptrL, direction, x - cellSize, y);
	elseif(direction == 3) then		-- Right --
		return MoveEnemy(ptr, ptrL, direction, x + cellSize, y);
	end
	return false
end

function MoveEnemy(ptr, ptrL, dir, x, y)
	-- Check if the a obstacle or enemy is in the way of the enemy, if not move to the cell
	if (NoObstacle(x, y) and NoEnemy(x, y) and NoDoor(x, y)) then
		ptr:SetEnemyInt(dir, ptrL, "SetDirection")
		ptr:SetEnemyPosition(x, y, ptrL, "SetPosition")
		return true
	end
	return false
end