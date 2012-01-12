#include "System.h"
#include "Sprite.h"

void enqueue() const {
    const std::shared_ptr<const IDepth> spthis = shared_from_this();
    System::get().depthEnqueue(spthis);
}
