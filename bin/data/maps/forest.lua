spawn("forest")
while true do
    local enemy = spawn_hook("planeE1")
    pos(enemy, 300.0, -200.0)
    vel(enemy, 0.0, 100.0)
    unhook(enemy)
    coroutine.yield(30)
end

