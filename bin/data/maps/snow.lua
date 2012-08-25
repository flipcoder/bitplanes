SCREEN_W = 320
SCREEN_H = 480

spawn("snow")

i = 0
while i < 100 do
    types = { "planeE1", "planeE2", "mine" }
    local bad = spawn_hook(types[math.random(1,3)])
    x, y = pos(bad)
    szx, szy = size(bad)
    pos(mine,
        (math.random() * SCREEN_W) - szx/2,
        y
    )
    unhook(bad)
    i = i + 1
    coroutine.yield(10)
end

repeat coroutine.yield() until clear()

