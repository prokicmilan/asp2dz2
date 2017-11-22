#include "process.h"

int Process::prevID = 0;

template <typename T>
void Process::write(T& t) const {
	t << pid << ":" << name << " (" << executionTime << ", " << waitingTime << ")";
}


Process::Process(const std::string & name, const long timeToComplete, const long maxWaitingTime) {
	this->name = name;
	this->timeToComplete = timeToComplete;
	this->maxWaitingTime = maxWaitingTime;
	executionTime = 0;
	waitingTime = 0;
	pid = ++prevID;
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

int Process::getPid() const {
	return pid;
}


void Process::setWaitingTime(const long time) {
	waitingTime = time;
}

void Process::setPid(int pid) {
	this->pid = pid;
}

void Process::updateWaitingTime(const long time) {
	waitingTime += time;
}

long Process::updateExecutionTime(const long time) {
	if (executionTime + time >= timeToComplete) {
		int res = timeToComplete - executionTime;
		executionTime = timeToComplete;
		return res;
	}
	else {
		executionTime += time;
		return time;
	}
}

std::ostream& operator<<(std::ostream &os, const Process &p) {
	p.write(os);
	return os;
}