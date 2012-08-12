#ifndef _IFALLIBLE_H
#define _IFALLIBLE_H

#include "Util.h"
#include <iostream>

class IFallible
{
    protected:

        class Failure : public std::runtime_error {
            public:
                Failure(): std::runtime_error("Runtime Error") {}
                Failure(const char* err): std::runtime_error(err) {}
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

