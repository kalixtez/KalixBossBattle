KALIX_X = 200
KALIX_Y = 200
KALIX_SPEED_X = 160
KALIX_SPEED_Y = 300
HEALTH = 100
JUMPING = false
json_path = "C:\\Users\\OmGIt\\OneDrive\\Escritorio\\C++ practice\\KalixBossBattle\\assets\\kalix_spt\\player.json"
total_elapsed = 0

animationList = LoadAnimations(ENTITY_PTR, json_path)

CURRENT_ANIMATION = animationList["IdleOne"]
PAST_ANIMATION = nil

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
    if KALIX_SPEED_Y <= -300 then
      JUMPING = false
      KALIX_SPEED_Y = 300
    end
  end
end

function Main(ptr, time)
  DIRX, JUMPING_L = GetStatus(ptr)

  total_elapsed = total_elapsed + time
  --animationID = GetCurrentAnimation(ptr)
  if DIRX == 0 and JUMPING_L == false
    CURRENT_ANIMATION = animationList["IdleOne"]
  end
  if DIRX == 1 and JUMPING_L == false
    CURRENT_ANIMATION = animationList["Running"]
  else if DIRX == -1 and JUMPING_L == false
    CURRENT_ANIMATION = animationList["Running"]
  end

  if PAST_ANIMATION != CURRENT_ANIMATION --reset() will set the m_FirstTime, m_currentFrame and m_AnimationTime to true, 0, and 0.0, so that when the animation is ever played again, it starts from the beginning.
    PAST_ANIMATION:reset() --If the past animation is not the same as the current, which means we changed animations this frame, the past animation will be reset.
    CURRENT_ANIMATION:play(ENTITY_PTR) -- Play will set the m_CurrentAnimation of the object to the CURRENT_ANIMATION userdata.
  end
  PAST_ANIMATION = CURRENT_ANIMATION

  if total_elapsed > 0.065 then
    CURRENT_ANIMATION:next_frame()
    total_elapsed = 0
  end

  if JUMPING_L == true then
    Update(DIRX, time, JUMPING_L)
    CURRENT_ANIMATION = animationList["Jumping"]
  else
    Update(DIRX, time, JUMPING)
  end

  return KALIX_X, KALIX_Y, JUMPING, animationID, frametime
end
