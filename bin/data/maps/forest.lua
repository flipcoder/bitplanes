spawn("forest")
music("sea")

coroutine.yield(100)

repeat coroutine.yield() until clear()

