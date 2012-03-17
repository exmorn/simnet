#include "blockingqueue.h"
namespace simnet
{
    BlockingQueue::BlockingQueue()
		: m_mutex()
		, m_cond_notEmpty(m_mutex)
		, m_queue()
	{
	}
	void BlockingQueue::put(const T& x)
	{
		MutexLockGuard lock(m_mutex);
		m_queue.push_back(x);
		m_cond_notEmpty.notify();
	}
	T BlockingQueue::take()
	{
		MutexLockGuard lock(m_mutex);
		while(m_queue.empty())
		{
			m_cond_notEmpty.wait();
		}
		assert(!m_queue.empty());
		T front(m_queue.front());
		m_queue.pop_front();
		return front;
	}
	size_t BlockingQueue::size()
	{
		MutexLockGuard lock(m_mutex);
		return m_queue.size();
	}
}