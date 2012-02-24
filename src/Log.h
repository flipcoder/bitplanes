#ifndef _LOG_H
#define _LOG_H
#pragma once

#include <string>
#include <fstream>
#include <boost/circular_buffer.hpp>
#include "IStaticInstance.h"

class Log : public IStaticInstance<Log>
{
public:

    class Message
    {
    public:
        std::string sMessage;
        enum eLoggingLevel { LL_BLANK, LL_INFO, LL_DEBUG, LL_WARNING, LL_ERROR } eLevel;

        Message(std::string message, eLoggingLevel level):
            sMessage(message),
            eLevel(level) {}
    };

private:

    boost::circular_buffer<Message> m_cbLog;
    std::ofstream m_LogFile;
    bool m_bStdOut;

    static const int DEFAULT_LENGTH = 256;

public:
    //static Log& get()
    //{
    //    static Log log;
    //    return log;
    //}
    
    Log();
    virtual ~Log();

    void write(const std::string& s, Message::eLoggingLevel lev = Message::LL_INFO);
    void warning(const std::string&s) { write(s,Message::LL_WARNING); }
    void error(const std::string&s) {write(s,Message::LL_ERROR);}

    unsigned int size() const { return m_cbLog.size(); }
    bool empty() const { return (size()==0); }
    void setStdOut(bool b) { m_bStdOut=b; }

    boost::circular_buffer<Message>* getBuffer() { return &m_cbLog; }
    const boost::circular_buffer<Message>* getBuffer_c() const { return &m_cbLog; }
    std::string message(unsigned int idx) {
        if(idx < m_cbLog.size())
            return m_cbLog.at(idx).sMessage;
        return "";
    }
};


#endif
