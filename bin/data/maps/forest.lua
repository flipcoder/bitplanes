spawn("forest")
i = 0

while i < 320 do
    enemy = spawn_hook("planeE1")
    i = i + 50
    x, y = pos(enemy)
    pos(enemy, i, y)
    unhook(enemy)
    coroutine.yield(30)
end

while i > 0 do
    enemy = spawn_hook("planeE1")
    i = i - 50
    x, y = pos(enemy)
    pos(enemy, i, y)
    unhook(enemy)
    coroutine.yield(30)
end

frames = 0
while frames < 100 do
    enemy = spawn_hook("planeE1")
    x, y = pos(enemy)
    pos(enemy, math.random(320), y)
    vel(enemy, 0, math.random(50,200))
    unhook(enemy)
    frames = frames + 1
    coroutine.yield(10)
end

frames = 0
while frames < 200 do
    enemy = spawn_hook("planeE1")
    x, y = pos(enemy)
    pos(enemy, math.random(320), y)
    vel(enemy, 0, math.random(50,200))
    unhook(enemy)
    frames = frames + 1
    coroutine.yield(5)
end

