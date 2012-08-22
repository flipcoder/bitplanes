spawn("road")
i = 0
while i < 200 do
    local enemy = spawn_hook("planeE1")
    i = i + 20
    local x, y = pos()
    pos(enemy, i, y)
    unhook(enemy)
    coroutine.yield(30)
end

