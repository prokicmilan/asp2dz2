#include "process.h"

Process::Process(const std::string & name, const long timeToCopmlete, const long maxWaitingTime) {
	this->name = name;
	this->timeToComplete = timeToComplete;
	this->maxWaitingTime = maxWaitingTime;
	executionTime = 0;
	waitingTime = 0;
}

std::string Process::getName() const {
	return name;
}

long Process::getTimeToComplete() const {
	return timeToComplete;
}

long Process::getMaxWaitingTime() const {
	return maxWaitingTime;
}

long Process::getWaitingTime() const {
	return waitingTime;
}

long Process::getExecutionTime() const {
	return executionTime;
}

void Process::setWaitingTime(const long time) {
	waitingTime = time;
}

void Process::updateWaitingTime(const long time) {
	waitingTime += time;
}

void Process::updateExecutionTime(const long time) {
	executionTime += time;
}

std::ostream & operator<<(std::ostream & os, const Process & p)
{
	os << p.name << " (" << p.executionTime << ", " << p.waitingTime << ")";

	return os;
}
