#ifndef __MUTEXLOCK_H__
#define __MUTEXLOCK_H__
#include "noncopyable.h"
#include "SPThread.h"
#include "types.h"
#include<assert.h>
namespace simnet
{
	class MutexLock : noncopyable
	{
	private:
		sp_thread_mutex_t m_mutex;
		pid_t m_holder;
	public:
		MutexLock();
		~MutexLock();
		void lock();
		void unlock();
		sp_thread_mutex_t* getThreadMutex();
		bool isLockedByThisThread();
		void assertLocked();
	};

	class MutexLockGuard : noncopyable
	{
	private:
		MutexLock& m_mutexLock;
	public:
		MutexLockGuard(MutexLock& mutexLock);
		~MutexLockGuard();
	};
}
#endif