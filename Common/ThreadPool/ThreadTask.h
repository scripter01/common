#ifndef THREAD_TASK_H
#define THREAD_TASK_H

class ThreadTask
{
public:
	virtual ~ThreadTask() = default;
	virtual void run() {};// = 0;
};

#endif //THREAD_TASK_H