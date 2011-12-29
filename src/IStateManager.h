#ifndef _STATE_MANAGER_H
#define _STATE_MANAGER_H

#include <memory>
#include <stack>

template <class tID, class tState>
class IStateManager
{
    public:
        enum eOperation {
            OP_NONE = 0,
            OP_PUSH,
            OP_POP,
            OP_SWAP,
            OP_CLEAR,
        };
        //enum eScheduledTime {
        //    ST_POLL = 0,
        //    ST_NOW,
        //};
        //enum eUrgency {
        //    U_NORMAL = 0,
        //    U_FORCE
        //};

    private:

        std::stack<tState*> m_sState;
        tState* m_pPreserved;

        eOperation m_Operation;
        tID m_OperandID;

        bool m_bFast;

        void nullify() {
            m_bFast = false;
        }

        // stack wrapper methods
        void stackPush(tState* s) {
            assert(s);
            m_sState.push(s);
        }
        void stackPop() {
            if(m_sState.empty())
                return;
            freeState(m_sState.top());
            m_sState.pop();
        }
        tState* stackPreserve() {
            if(m_sState.empty())
                return nullptr;
            tState* s = m_sState.top();
            m_sState.pop();
            return s;
        }
        tState* stackTop() {
            if(!stackEmpty())
                return m_sState.top();
            else
                return nullptr;
        }
        const tState* stackTop() const {
            if(!stackEmpty())
                return m_sState.top();
            else
                return nullptr;
        }
        bool stackEmpty() const {
            return m_sState.empty();
        }
        void stackClear() {
            while(!stackEmpty())
                stackPop();
        }

        
        virtual bool isNullID(const tID tid) const {
            return tid == tID();
        }
        virtual const tID nullID() { return tID(); }
        
    public:
        IStateManager() {
            nullify();
        }
        virtual ~IStateManager() {
            m_bFast = true; // no timed transitions
            stackClear();
        }

        void popState() {
            m_Operation = OP_POP;
        }
        void pushState(tID id) {
            m_Operation = OP_PUSH;
            m_OperandID = id;
                
        }
        void swapState(tID id) {
            m_Operation = OP_SWAP;
            m_OperandID = id;
        }
        void clearStates() {
            m_Operation = OP_CLEAR;
        }
        void clearToState(tID id) {
            m_Operation = OP_CLEAR;
            m_OperandID = id;
        }

        tState* currentState() {
            return stackTop();
        }
        const tState* currentState() const {
            return stackTop();
        }

        bool schedule(eOperation op, tID id = nullID()) {
            if(pending())
                return false; // already scheduled
            m_Operation = op;
            m_OperandID = id;
            return true;
        }
        
        // returns false if stack is empty
        bool pollState() {

            if(m_Operation == OP_NONE)
                return !stackEmpty();
            else if(m_Operation == OP_POP)
                stackPop();
            else if(m_Operation == OP_PUSH)
            {
                tState* s = newState(m_OperandID);
                if(s)
                    m_sState.push(s);
            }
            else if(m_Operation == OP_SWAP)
            {
                stackPop();
                tState* s = newState(m_OperandID);
                if(s)
                    m_sState.push(s);
            }
            else if(m_Operation == OP_CLEAR)
            {
                stackClear();
                if(!isNullID(m_OperandID))
                {
                    tState* s = newState(m_OperandID);
                    if(s)
                        m_sState.push(s);
                }
            }
            else
               assert(false); // invalid operation

            m_Operation = OP_NONE;

            // check stack again
            return !stackEmpty();
        }

        bool pending() const {
            return m_Operation != OP_NONE;
        }

        // factory overload for state creation
        // note: preserved may be NULL
        virtual tState* newState(const tID id) = 0;

        // optional overload
        virtual void freeState(const tState* s) {
            delete s;
        }
};

#endif

