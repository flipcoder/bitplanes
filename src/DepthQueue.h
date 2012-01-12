#ifndef _DEPTHQUEUE_H
#define _DEPTHQUEUE_H

#include <queue>
#include <memory>
#include "Util.h"
#include "IDepth.h"

class DepthQueue
{
    public:

        class DepthCompare
        {
            public:
                bool operator() (
                    const std::weak_ptr<IDepth>& s,
                    const std::weak_ptr<IDepth>& s2) const
                {
                    std::shared_ptr<IDepth> sp = s.lock();
                    std::shared_ptr<IDepth> sp2 = s2.lock();
                    if(sp && sp2)
                        return sp->depth() < sp2->depth();
                    else
                        return false;
                }
        };

    private:

        std::priority_queue<std::weak_ptr<IDepth>, std::vector<std::weak_ptr<IDepth>>, DepthCompare> m_pqQueue;

    public:
        
        DepthQueue() {}
        virtual ~DepthQueue() {}

        void enqueue(const std::shared_ptr<IDepth>& s) {
            //m_pqQueue.push(std::weak_ptr<IDepth>(s));
        }

        virtual void render() {
            while(!m_pqQueue.empty()) {
                std::shared_ptr<IDepth> s = m_pqQueue.top().lock();
                if(s)
                    s->render();
                m_pqQueue.pop();
            }
        }
};

#endif

