backdrop("space")
music("sea")

coroutine.yield(10)

-- let's make a maze !

tile = 40
tiles = SCREEN_W / tile
layers = 0
open = math.random(0, tiles) * tile
while layers < 25 do
    c = 0
    open = open + (math.random(0,5) - 2) * tile
    
    if open/tile >= tiles then
        open = tile * (tiles - 1)
    end
    if open/tile <= 0 then
        open = 0
    end
    
    while c <= tiles*tile do
        if c ~= open then
            local rock = spawn_hook("debrisSpace4")
            pos(rock, c, 0)
            vel(rock, 0, 300)
            --x, y = size(rock)
            unhook(rock)
        end
        c = c + tile
    end
    coroutine.yield(25)
    layers = layers + 1
end
repeat coroutine.yield() until clear()

-- now random asteroids with ships!

frames = 0
while frames < 100 do
    local enemy = spawn_hook("debrisSpace4")
    x, y = pos(enemy)
    pos(enemy, math.random(SCREEN_W), y)
    vel(enemy, (math.random(0,1) * 2 - 1) * math.random(10,30), math.random(100,200))
    unhook(enemy)
    frames = frames + 1
    if math.random(0,20) == 0 then
        local plane = spawn_hook("planeE4")
        x,y = pos(plane)
        sx,sy = size(plane)
        pos(enemy, math.random(SCREEN_W), 0)
        vel(enemy, (math.random(0,1) * 2 - 1) * math.random(100), math.random(50,100))
        unhook(enemy)
    end
    if math.random(0,20) == 0 then
        local plane = spawn_hook("planeE5")
        x,y = pos(plane)
        sx,sy = size(plane)
        vel(enemy, (math.random(0,1) * 2 - 1) * math.random(100), math.random(10,20))
        pos(enemy, math.random(SCREEN_W), 0)
        unhook(enemy)
    end
    coroutine.yield(10)
end

-- boss?
    
repeat coroutine.yield() until clear()

