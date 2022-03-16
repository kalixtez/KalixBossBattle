KALIX_X = 200
KALIX_Y = 200
KALIX_SPEED_X = 160
KALIX_SPEED_Y = 160
HEALTH = 100
JUMPING = false
json_path = "C:\\Users\\OmGIt\\OneDrive\\Escritorio\\C++ practice\\KalixBossBattle\\assets\\kalix_spt\\player.json"
total_elapsed = 0

animationList = LoadAnimations(ENTITY_PTR, json_path)

function Update(DIRX, TIME, JUMPING_L)
  KALIX_X = KALIX_X + (DIRX * KALIX_SPEED_X * TIME)
  JUMPING = JUMPING_L
  if JUMPING == true then
    if KALIX_SPEED_Y >= 0 then
      KALIX_Y = KALIX_Y - (KALIX_SPEED_Y * TIME)
      KALIX_SPEED_Y = KALIX_SPEED_Y - 6
    else
      KALIX_Y = KALIX_Y - (KALIX_SPEED_Y * TIME)
      KALIX_SPEED_Y = KALIX_SPEED_Y - 6
    end
    if KALIX_SPEED_Y <= -80 then
      JUMPING = false
      KALIX_SPEED_Y = 160
    end
  end
end

function Main(ptr, time)
  DIRX, JUMPING_L = GetStatus(ptr)
  ELAPSEDTIME = time
  total_elapsed = total_elapsed + time
  animationID = GetCurrentAnimation(ptr)
  --frametime = animtable.frametime(animationList[animationID])
  --if total_elapsed > animationList[animationID]:get_frametime() then
  --animationList.Running:next_frame()
  if total_elapsed > 0.064 then
    animtable.next_frame(animationList[animationID])
    total_elapsed = 0
  end
    --total_elapsed = 0
  --end

  if JUMPING_L == true then
    Update(DIRX, ELAPSEDTIME, JUMPING_L)
  else
    Update(DIRX, ELAPSEDTIME, JUMPING)
  end

  return KALIX_X, KALIX_Y, JUMPING, animationID, total_elapsed
end
