#ifndef __CONDITION_H__
#define __CONDITION_H__
#include "noncopyable.h"
#include "SpThread.h"
#include "types.h"
#include "MutexLock.h"
namespace simnet
{
	class Condition : noncopyable
	{
	private:
		MutexLock& m_mutex;
		sp_thread_cond_t m_cond;
	public:
		explicit Condition( MutexLock& mutex);
		~Condition();
		void wait();
		void notify();
	};
}
#endif