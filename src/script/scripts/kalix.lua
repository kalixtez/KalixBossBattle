
KALIX_X = 0
KALIX_Y = 0
KALIX_SPEED_X = 3
KALIX_SPEED_Y = 3
HEALTH = 0
JUMPING = false

function Init(ptr)
  KALIX_X, KALIX_Y, HEALTH = GetInitials(ptr)
end

function HandleInput(ptr)
  DIRX, JUMPING = GetDirection(ptr)
  time = GetTime()
end

function Update(DIRX, DIRY, time)

KALIX_X = KALIX_X + (DIR * SPEED * TIME)
if JUMPING == true


end


function Draw(ptr)
  DrawEntity(KALIX_X, KALIX_Y, ptr)

end

function Main(ptr)
  HandleInput(ptr)
  --Here goes the drawing code.
  Draw(ptr)
end
