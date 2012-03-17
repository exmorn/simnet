#include "condition.h"
namespace simnet
{
    Condition::Condition( MutexLock& mutex)
		: m_mutex(mutex)
	{
		sp_thread_cond_init(&m_cond, NULL);
	}
	Condition::~Condition()
	{
		sp_thread_cond_destroy(&m_cond);
	}
	void Condition::wait()
	{
		sp_thread_cond_wait(&m_cond, m_mutex.getThreadMutex());
	}
	void Condition::notify()
	{
		sp_thread_cond_signal(&m_cond);
	}
}