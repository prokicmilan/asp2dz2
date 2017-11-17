#pragma once

#include <string>

class Process {
public:
	Process(const std::string &name, const long timeToCopmlete, const long maxWaitingTime);
	
	//getters
	std::string getName() const;
	long getTimeToComplete() const;
	long getMaxWaitingTime() const;
	long getWaitingTime() const;
	long getExecutionTime() const;

	//setters
	void setWaitingTime(const long time);
	
	//updaters
	void updateWaitingTime(const long time);
	void updateExecutionTime(const long time);

	//operator overload
	friend std::ostream& operator<<(std::ostream &os, const Process &p);

private:
	std::string name;
	long timeToComplete;
	long maxWaitingTime;
	long waitingTime;
	long executionTime;
};