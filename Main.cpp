#include <iostream>
#include "EventQueue.h"

int main()
{
	int cpuNum;
	int ioDevice;
	double taskFreq;
	double switchCost;
	double taskMix;

	std::cout << "Enter Task Frequency (how often tasks are created): ";
	std::cin >> taskFreq;
	std::cout << "Enter Task Mix (decimal between 0 andn 1): ";
	std::cin >> taskMix;
	std::cout << "Enter Number of CPUs: ";
	std::cin >> cpuNum;
	std::cout << "Enter Number of I/O Devices: ";
	std::cin >> ioDevice;
	std::cout << "Enter Cost of Context Switch: ";
	std::cin >> switchCost;

	EventQueue event_q(cpuNum, taskMix, taskFreq, ioDevice, switchCost); 
	//EventQueue event_q(2, .6, 5, 2, 1);
	std::cout << std::endl;
	std::cout << std::endl;
	event_q.start_simulator();
	return 0;
}