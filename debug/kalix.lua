KALIX_X = 50
KALIX_Y = 50
KALIX_SPEED_X = 5
KALIX_SPEED_Y = 0
HEALTH = 100

function Update(DIRX, TIME, JUMPING)
  KALIX_X = KALIX_X + (DIRX * KALIX_SPEED_X * TIME)
  if JUMPING == true then
    if KALIX_SPEED_Y > 0 then
      KALIX_Y = KALIX_Y - (KALIX_SPEED_Y * TIME)
      KALIX_SPEED_Y = KALIX_SPEED_Y + 0.25
    else
      KALIX_Y = KALIX_Y - (KALIX_SPEED_Y * TIME)
      KALIX_SPEED_Y = KALIX_SPEED_Y - 0.25
      if KALIX_SPEED_Y <= -3 then
        JUMPING = false
      end
    end
  end
end

function Main(ptr, time)
  DIRX, JUMPING = GetStatus(ptr)
  ELAPSEDTIME = time
  Update(DIRX, ELAPSEDTIME, JUMPING)

  return KALIX_X, KALIX_Y
end
