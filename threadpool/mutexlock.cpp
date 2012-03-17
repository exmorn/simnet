#include "mutexlock.h"
namespace simnet
{
    MutexLock::MutexLock()
		: m_holder(NULL)
	{
		sp_thread_mutex_init(&m_mutex, NULL);
	}
	MutexLock::~MutexLock()
	{
		assert(m_holder == 0);
		sp_thread_mutex_destroy(&m_mutex);
	}
	void MutexLock::lock()
	{
		sp_thread_mutex_lock(&m_mutex);
		m_holder = sp_thread_self();
	}
	void MutexLock::unlock()
	{
		m_holder = 0;
		sp_thread_mutex_unlock(&m_mutex);
	}
	sp_thread_mutex_t* MutexLock::getThreadMutex()
	{
		return &m_mutex;
	}
	bool MutexLock::isLockedByThisThread()
	{
		return m_holder == sp_thread_self();
	}
	void MutexLock::assertLocked()
	{
		assert(isLockedByThisThread());
	}
    MutexLockGuard::MutexLockGuard(MutexLock& mutexLock)
			    : m_mutexLock(mutexLock)
    {
	    m_mutexLock.lock();
    }
    MutexLockGuard::~MutexLockGuard()
    {
	    m_mutexLock.unlock();
    }
}