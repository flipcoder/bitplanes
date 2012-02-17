#ifndef _FALLIBLE_H
#define _FALLIBLE_H

#include "Util.h"

class IFallible
{
    protected:

        class Failure : public std::runtime_error {
            public:
                Failure(): std::runtime_error("failure") {}
        };

        virtual void setError(const std::string& err){
            m_sError = err;
            std::cout << "Error: " << err << std::endl;
        }

    public:

        IFallible() {}
        virtual ~IFallible() {}

        virtual bool hasError() const { return !m_sError.empty(); }
        virtual std::string getError() const { return m_sError; }
        virtual std::string moveError() { return std::move(m_sError); }

    private:

        std::string m_sError;
};

#endif

