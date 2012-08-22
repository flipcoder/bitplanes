#include "Particle.h"
#include "Util.h"
#include "Freq.h"

void Particle :: collisionEvent(std::shared_ptr<Object>& object)
{
    if(object->solid())
    {
        IOwnable* owned;
        if(owned = dynamic_cast<IOwnable*>(object.get()))
            if(owner() && owned->owner() && owned->owner() != owner()) // diff owner?
            {

                std::shared_ptr<Object> impact(
                    new Particle(
                        str("data/objects/explosionSmall.png"),
                        Freq::Time(250)
                    )
                );

                impact->pos(pos() + size()/2.0f - impact->size()/2.0f);
                //impact->sprite().depth(100.0f);
                world()->add(impact);
                invalidate();
            }
    }
}

