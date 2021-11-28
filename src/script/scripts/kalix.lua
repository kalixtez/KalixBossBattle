
KALIX_X = 200
KALIX_Y = 200
KALIX_SPEED_X = 3
KALIX_SPEED_Y = 3
HEALTH = 100
JUMPING = false
DIRX = 0
ELAPSEDTIME = 0

function Update(DIRX, TIME, JUMPING)
  KALIX_X = KALIX_X + (DIR * SPEED * TIME)
  if JUMPING == true then
    if KALIX_SPEED_Y > 0 then
      KALIX_Y = KALIX_Y - (KALIX_SPEED_Y * TIME)
      KALIX_SPEED_Y -= 0.25
    else
      KALIX_Y = KALIX_Y - (KALIX_SPEED_Y * TIME)
      KALIX_SPEED_Y -= 0.25
      if KALIX_SPEED_Y <= -3
        JUMPING = false
      end
    end
  end
end

function Main(ptr, time)
  DIRX, JUMPING = GetStatus(ptr)
  ELAPSEDTIME = time
  Update(DIRX, ELAPSEDTIME, JUMPING)
end
