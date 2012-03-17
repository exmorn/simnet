#include "thread.h"
namespace simnet{
    pid_t currentThreadId()
    {
        return sp_thread_self();
    }
    void Thread::runInThread()
	{
		m_exec();
	}
    Thread::Thread(const executive& func, const std::string& name)
			: m_started(false)
			, m_thread_id(0)
			, m_tid(0)
			, m_exec(func)
			, m_name(name)
	{
	}
    Thread::~Thread(){}
    bool Thread::started() const
	{ 
        return m_started;
    }
    pid_t Thread::tid() const 
	{ 
        return m_tid; 
    }
    const std::string Thread::name() const
	{
        return m_name;
    }
    void Thread::start()
	{
		assert(!m_started);
		m_started = true;
		sp_thread_create(&m_thread_id, NULL, &startThread, this);
	}
}
