#include "threadpool.h"
#include<boost/bind.hpp>
#include<assert.h>
#include "exception.h"
#pragma warning(disable:4996)
namespace simnet
{
	ThreadPool::ThreadPool(const string& name)
		: m_mutex()
		, m_cond(m_mutex)
		, m_name(name)
		, m_running(false)
	{
	}

	ThreadPool::~ThreadPool(void)
	{
	}
	void ThreadPool::start(int num_threads)
	{
		assert(m_threads.empty());
		m_running = true;
		m_threads.reserve(num_threads);
		int i = 0;
		while(i < num_threads)
		{
			char id[32];
			sprintf(id, "%d", i);
            Thread* pTd = new Thread(boost::bind(&ThreadPool::runInThread, this), m_name + id);
			m_threads.push_back(pTd);
			m_threads[i].start();
            i++;
		}
	}
	void ThreadPool::stop()
	{

	}

	void ThreadPool::run(const Task& task)
	{
		if(m_threads.empty())
		{
			task();
		}
		else
		{
			MutexLockGuard(this->m_mutex);
			m_task_queue.push_back(task);
			m_cond.notify();
		}	
	}
	ThreadPool::Task ThreadPool::take()
	{
		MutexLockGuard lock(m_mutex);
		while(m_running && m_task_queue.empty())
			m_cond.wait();
		assert(!m_task_queue.empty());
		Task task;
		task = m_task_queue.front();
		m_task_queue.pop_front();
		return task;
	}
	void ThreadPool::runInThread()
	{
		try
		{
			while(m_running)
			{
				Task task;
				task = static_cast<Task>(take());
				if(task)
					task();
			}
		}
		catch (const Exception& ex)
		{
			fprintf(stderr, "exception caught in ThreadPool %s\n", m_name.c_str());
			fprintf(stderr, "reason: %s\n", ex.what());
			abort();
		}
		catch (const std::exception ex)
		{
			fprintf(stderr, "exception caught in ThreadPool %s\n", m_name.c_str());
			fprintf(stderr, "reason: %s\n", ex.what());
			abort();
		}
		catch (...)
		{
			fprintf(stderr, "unknown exception caught in ThreadPool %s\n", m_name.c_str());
			abort();
		}
	}
}