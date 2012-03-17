#ifndef __THREAD_H__
#define __THREAD_H__
#include<boost/function.hpp>
#include<boost/bind.hpp>
#include "noncopyable.h"
#include "Condition.h"
#include "MutexLock.h"
#include "spthread.h"
#include "types.h"
#include "ObjCounter.h"
#include<string>
#include<assert.h>
namespace simnet
{	
    pid_t currentThreadId();
	class Thread : noncopyable
	{
	public:
		typedef boost::function<void ()> executive;
	private:
		bool m_started;
		pid_t m_tid;
		std::string m_name;
		executive m_exec;
		ObjCounter<Thread> m_threadCnt;
		static sp_thread_result_t _stdcall Thread::startThread(void* obj)
        {
	        Thread* thread = static_cast<Thread *>(obj);
	        thread->runInThread();
	        return NULL;
        }
		void runInThread();
	public:

		explicit Thread(const executive& func, const std::string& name);

		~Thread();

		bool started() const;

		pid_t tid() const;

		const std::string name() const;
		
		void start();
	};
}
#endif