#include "Particle.h"
#include "Util.h"
#include "Freq.h"
#include "Filesystem.h"

void Particle :: collisionEvent(std::shared_ptr<Object>& object)
{
    if(object->solid())
    {
        IOwnable* owned;
        if(owned = dynamic_cast<IOwnable*>(object.get()))
            if(owner() && owned->owner() && owned->owner() != owner()) // diff owner?
            {

                std::string impact_fn;
                if(properties().getStringValue("events", "impact", impact_fn)
                    && Filesystem::hasExtension(impact_fn, "ini")) // make sure event is not a script
                {
                    std::shared_ptr<Object> impact(new Particle(impact_fn));
                    impact->pos(pos() + size()/2.0f - impact->size()/2.0f);
                    world()->add(impact);
                }
                invalidate();
            }
    }
}

