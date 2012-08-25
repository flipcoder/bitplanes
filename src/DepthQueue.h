#ifndef _DEPTHQUEUE_H
#define _DEPTHQUEUE_H

#include <queue>
#include <memory>
#include "Util.h"
#include "IDepthSortable.h"
#include "IMovable.h"

class DepthQueue
{
    public:

        class DepthCompare
        {
            public:
                bool operator() (
                    const std::weak_ptr<const IDepthSortable>& s,
                    const std::weak_ptr<const IDepthSortable>& s2) const
                {
                    std::shared_ptr<const IDepthSortable> sp = s.lock();
                    std::shared_ptr<const IDepthSortable> sp2 = s2.lock();
                    if(sp && sp2){
                        // if the same depth, sort by y pos instead (to prevent z-fighting)
                        if(floatcmp(sp->depth(), sp2->depth()))
                        {
                            const IMovable* m = dynamic_cast<const IMovable*>(sp.get());
                            const IMovable* m2= dynamic_cast<const IMovable*>(sp2.get());
                            if(m && m2)
                                return m->y() < m2->y();
                            else
                                return false;
                           // sort by y pos instead
                        }
                        return sp->depth() < sp2->depth();
                    }
                    else
                        return false;
                }
        };

    private:

        std::priority_queue<std::weak_ptr<const IDepthSortable>, std::vector<std::weak_ptr<const IDepthSortable>>, DepthCompare> m_pqQueue;

    public:
        
        DepthQueue() {}
        virtual ~DepthQueue() {}

        void enqueue(const std::shared_ptr<const IDepthSortable>& s) {
            m_pqQueue.push(std::weak_ptr<const IDepthSortable>(s));
        }

        virtual void render() {
            while(!m_pqQueue.empty()) {
                std::shared_ptr<const IDepthSortable> s;
                if(s = m_pqQueue.top().lock())
                    s->render();
                m_pqQueue.pop();
            }
        }
};

#endif

