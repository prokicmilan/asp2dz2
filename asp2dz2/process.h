#pragma once

#include <string>

class Process {
public:
	Process(const std::string &name, long timeToCopmlete, long maxWaitingTime);
	Process(const Process &p) = default;
	
	//getters
	std::string getName() const;
	long getTimeToComplete() const;
	long getMaxWaitingTime() const;
	long getWaitingTime() const;
	long getExecutionTime() const;
	int getPid() const;

	//setters
	void setWaitingTime(const long time);
	void setPid(int pid);
	
	//updaters
	void updateWaitingTime(const long time);
	long updateExecutionTime(const long time);

	//operator overload
	bool operator<(const Process &p) const;
	bool operator<=(const Process &p) const;
	bool operator>(const Process &p) const;
	bool operator>=(const Process &p) const;
	bool operator==(const Process &p) const;
	bool operator!=(const Process &p) const;
	friend std::ostream& operator<<(std::ostream &os, const Process &p);

private:
	int pid;
	static int prevID;
	std::string name;
	long timeToComplete;
	long maxWaitingTime;
	long waitingTime;
	long executionTime;

	template<typename T>
	void write(T &t) const;
};