#pragma once
#include <queue>
#include <string>
#include <time.h>
#include <stdlib.h>

struct Burst
{
public:
	double duration;
	std::string type;
	int io_id;

	Burst(std::string t, double d)
	{
		duration = d;
		type = t;
	}
};

struct CPUBurst : public Burst
{
public:
	CPUBurst(std::string type, int t) : Burst(type, t)
	{
		io_id = -1;
	}
};

struct IOBurst : public Burst
{
public:
	IOBurst(std::string type, double t, int index) : Burst(type, t)
	{
		io_id = index;
	}
};

class Task
{
private:
	int start_time;
	int end_time;
	int end_of_first_io;
	std::vector<Burst> bursts;
	int current_burst;
	bool reached_io;
	int response_time;

public:
	Task() {}
	Task(std::string task_type, int s_time, int io_devices)		//io_devices is the max number of io_devices to choose from
	{
		start_time = s_time;
		current_burst = 0;
		srand(time(NULL));

		int job_count = rand() % (25) + 5;
		for (int i = 0; i < job_count; i++)
		{
			int t;
			if (i == 0 || i % 2 == 0 || i == job_count - 1)
			{
				// cpu burst
				if (task_type == "cpu") t = rand() % (50 + 1) + 20;
				else t = rand() % 15 + 1;
				CPUBurst job("cpu", t);
				bursts.push_back(job);
			}
			else
			{
				// io task
				if (task_type == "io") t = rand() % (50 + 1) + 20;
				else t = rand() % 15 + 1;
				int device_index = rand() % 2;
				IOBurst job("io", t, device_index);
				bursts.push_back(job);
			}
		}
	}

	void set_response_time(int current_time)
	{
		if (!reached_io)
		{
			reached_io = true;
			response_time = current_time - start_time;
		}
	}

	void done_job()
	{
		current_burst++;
	}

	bool is_done(int current_time)
	{
		if (current_burst >= bursts.size())
		{
			end_time = current_time;
			return true;
		}
		else return false;
	}

	Burst get_job()
	{
		Burst b = bursts[current_burst];
		return b;
	}

	int get_response_time()
	{
		return response_time - start_time;
	}

	int get_latency()
	{
		return end_time - start_time;
	}
};
