#ifndef THREAD_TASK_QUEUE_H
#define THREAD_TASK_QUEUE_H

template <typename T>
class ThreadTaskQueue
{
public:
	ThreadTaskQueue():
		m_valid(true)
	{}

	~ThreadTaskQueue()
	{
		invalidate();
	}

	bool waitPop(T& out)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		while (m_queue.empty() && m_valid)
			m_condition.wait(lock);
		//m_condition.wait(lock, [this]() {return !m_queue.empty() || !m_valid;} );
		if (!m_valid)
			return false;

		out = std::move(m_queue.front());
		m_queue.pop();
		return true;
	}

	void push(T value)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_queue.push(std::move(value));
		m_condition.notify_one();
	}

	void clear()
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		while (!m_queue.empty())
			m_queue.pop();
		m_condition.notify_all();
	}

	void invalidate()
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_valid = false;
		m_condition.notify_all();
	}

private:
	std::atomic_bool m_valid;
	mutable std::mutex m_mutex;
	std::queue<T> m_queue;
	std::condition_variable m_condition;
};

#endif //THREAD_TASK_QUEUE_H
