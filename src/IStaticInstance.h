#ifndef _ISTATICINSTANCE_H
#define _ISTATICINSTANCE_H

#include <memory>
#include "Util.h"

template<class T>
class IStaticInstance
{
    public:
        
        enum Flags {
            FREE = BIT(0)
        };
        static std::shared_ptr<T> shared(T* p = NULL, unsigned int flags = 0){
            static std::shared_ptr<T> instance;
            if(!(flags & FREE))
            {
                if(p)
                    instance.reset(p);
            }
            else
                instance.reset();
            return instance;
        }
        static std::weak_ptr<T> weak(){
            std::weak_ptr<T> w(shared());
            return w;
        }
        static T& get(T* p = NULL){
            return *shared(p);
        }
        static T* ptr(T* p = NULL){
            return &shared(p)->get();
        }
        static void reset() {
            shared(NULL, FREE);
        }
};

#endif

