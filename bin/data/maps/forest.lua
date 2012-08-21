while true do
    local enemy = spawn_hook("planeE1")
    vel(enemy, 0.0, 200.0)
    unhook(enemy)
    coroutine.yield(30)
end

