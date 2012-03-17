#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__
#include<boost/function.hpp>
#include "spthread.h"
#include "mutexlock.h"
#include "condition.h"
#include "thread.h"
#include "types.h"
#include<string>
#include<deque>
#include<boost/ptr_container/ptr_vector.hpp>
using namespace std;
namespace simnet
{
	class ThreadPool
	{
	public:
		typedef boost::function<void ()> Task;
	private:
		void runInThread();
		Task take();
		MutexLock m_mutex;
		Condition m_cond;
		string m_name;
		boost::ptr_vector<simnet::Thread> m_threads;
		deque<Task> m_task_queue;
		bool m_running;
	public:
		explicit ThreadPool(const string& name = string());
		~ThreadPool(void);
		void start(int num_threads);
		void stop();
		void run(const Task& f);
	};
	
}
#endif