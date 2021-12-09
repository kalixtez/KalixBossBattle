
KALIX_X = 200
KALIX_Y = 200
KALIX_SPEED_X = 3
KALIX_SPEED_Y = 5
HEALTH = 100
JUMPING = false

function Update(DIRX, TIME, JUMPING_L)
  KALIX_X = KALIX_X + (DIRX * KALIX_SPEED_X * TIME)
  JUMPING = JUMPING_L
  if JUMPING == true then
    if KALIX_SPEED_Y >= 0 then
      KALIX_Y = KALIX_Y - (KALIX_SPEED_Y * TIME)
      KALIX_SPEED_Y = KALIX_SPEED_Y - 0.25
    else
      KALIX_Y = KALIX_Y - (KALIX_SPEED_Y * TIME)
      KALIX_SPEED_Y = KALIX_SPEED_Y - 0.25
    end
    if KALIX_SPEED_Y <= -3 then
      JUMPING = false
      KALIX_SPEED_Y = 5
    end
  end
end

function Main(ptr, time)
  DIRX, JUMPING_L = GetStatus(ptr)
  ELAPSEDTIME = time
  if JUMPING_L == true then
    Update(DIRX, ELAPSEDTIME, JUMPING_L)
  else
    Update(DIRX, ELAPSEDTIME, JUMPING)
  end
  return KALIX_X, KALIX_Y, JUMPING
end
