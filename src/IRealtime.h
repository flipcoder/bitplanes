#ifndef _IREALTIME_H
#define _IREALTIME_H

class IRealtime : public IFallible
{
    public:
        virtual ~IRealtime() {};
        virtual bool logic(unsigned int advance) {return 1;}
        virtual void render() const {}
};

#endif

