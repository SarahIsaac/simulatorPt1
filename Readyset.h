#pragma once
#include <queue>

#include "Task.h"

class ReadySet
{
public:
	int idle_cpu_count;
	int total_cpu_count;
	std::queue<Task> task_queue;

	ReadySet() {}

	ReadySet(int cpu_count)
	{
		total_cpu_count = cpu_count;
		idle_cpu_count = cpu_count;
	}

	bool ableToAdd()
	{
		if (idle_cpu_count > 0) return true;
		else return false;
	}

	void add() { idle_cpu_count--; }

	void push(Task task)
	{
		task_queue.push(task);
	}

	void done()
	{
		idle_cpu_count++;
	}

	Task remove()
	{
		Task t = task_queue.front();
		task_queue.pop();
		return t;
	}
};