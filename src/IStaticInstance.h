#ifndef _ISTATICINSTANCE_H
#define _ISTATICINSTANCE_H

// A variation of a singleton, whereas a single static instance
// is selectable and assignable to be primary for a given class.
// Lifetime is controllable through a shared_ptr

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
			return &*shared(p);
		}
		static void reset() {
			shared(NULL, FREE);
		}
};

#endif

