#ifndef _FALLIBLE_H
#define _FALLIBLE_H

#include <string>

class IFallible
{
	protected:

		virtual void setError(const std::string& err){
			m_sError = err;
		}

	public:

		IFallible() {}
		virtual ~IFallible() {}

		virtual bool hasError() const { return !m_sError.empty(); }
		virtual std::string getError() const { return m_sError; }

	private:

		std::string m_sError;
};

#endif

