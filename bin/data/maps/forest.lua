spawn("forest")

coroutine.yield(100)

repeat coroutine.yield() until clear()

