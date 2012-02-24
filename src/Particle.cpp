#include "Particle.h"
#include "Util.h"
#include "Freq.h"

void Particle :: collisionEvent(std::shared_ptr<Object>& object) {
    if(object->solid()) {
        IOwner* owned;
        if(owned = dynamic_cast<IOwner*>(object.get()))
            if(owner() && owned->owner() && owned->owner() != owner())
            {

                std::shared_ptr<Object> impact(
                    new Particle(
                        str("data/gfx/objects/explosionSmall.png"),
                        Vector2(),
                        Freq::Time(250)
                    )
                );

                impact->pos() = pos() + size()/2.0f - impact->size()/2.0f;
                //impact->sprite().depth(100.0f);
                world()->add(impact);
                invalidate();
            }
    }
}

