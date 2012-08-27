backdrop("road")
music("road")

-- simple wave of planes
i = 0
while i < SCREEN_W do
    local enemy = spawn_hook("planeE1")
    i = i + 50
    x, y = pos(enemy)
    pos(enemy, i, y)
    unhook(enemy)
    coroutine.yield(30)
end

-- wave of planes (other direction)
while i > 0 do
    local enemy = spawn_hook("planeE1")
    i = i - 50
    x, y = pos(enemy)
    pos(enemy, i, y)
    unhook(enemy)
    coroutine.yield(30)
end


-- crazy batch of E2s
frames = 0
while frames < 100 do
    local enemy = spawn_hook("planeE2")
    x, y = pos(enemy)
    pos(enemy, math.random(SCREEN_W), y)
    vel(enemy, (math.random(0,1) * 2 - 1) * math.random(0,10), math.random(150,300))
    unhook(enemy)
    frames = frames + 1
    coroutine.yield(2)
end

-- batch of E1s
frames = 0
while frames < 100 do
    local enemy = spawn_hook("planeE1")
    x, y = pos(enemy)
    pos(enemy, math.random(SCREEN_W), y)
    vel(enemy, 0, math.random(150,300))
    unhook(enemy)
    frames = frames + 1
    coroutine.yield(10)
end

-- almost impossible
frames = 0
while frames < 200 do
    local enemy = spawn_hook("planeE1")
    x, y = pos(enemy)
    pos(enemy, math.random(SCREEN_W), y)
    vel(enemy, 0, math.random(150,300))
    unhook(enemy)
    frames = frames + 1
    coroutine.yield(5)
end

repeat coroutine.yield() until clear()


-- boss approaching
local boss = spawn_hook("horseshoe")
local sx, sy = size(boss)
while exists(boss) > 0 do
    x, y = pos(boss)
    if y >= -sy/2 then
        break
    end
    dx, dy = vel(boss)
    vel(boss, dx, dy+1)

    coroutine.yield()
end

-- boss wave
vel(boss, 0, -100)
i = 0
dir = 1
while exists(boss) > 0 do
    x, y = pos(boss)
    mid_x = (SCREEN_W / 2 - sx/2)

    -- flip direction
    i = i + .01
    if i > 1 then
        dir = math.random(0,1) * 2 - 1
        i = 0
    end

    -- wave pattern
    pos(boss,
        mid_x  +
        (
            dir * math.sin(i * math.pi) * mid_x
        ),
        - sy/2 +
        (
            math.sin(i * math.pi) * (sy/2)
        )
    )

    if math.random() < 0.2 then
        local enemy = spawn_hook("planeE2")
        esx, esy = size(enemy)
        pos(enemy, x + sx/2 - esx/2, y + sy - esy/2) -- spawn on boss
        vel(enemy, (math.random(0,1) * 2 - 1) * math.random(0,3)*10, math.random(150,300))
        unhook(enemy)
    end
    if math.random() < 0.1 * (1.0 -  (health(boss) / max_health(boss))) then
        local enemy = spawn_hook("planeE1")
        x, y = pos(enemy)
        pos(enemy, math.random(SCREEN_W), y)
        vel(enemy, 0, math.random(300,500))
        unhook(enemy)
    end

    coroutine.yield()
end

repeat coroutine.yield() until clear()

