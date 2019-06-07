#ifndef TASK_PERIOD_H_
#define TASK_PERIOD_H_

#include "task.h"

class Task_period : public Task {
	int period;
public :
	Task_period (const std::string& name, const std::string& data, int imp, int time, int period)  // создание задания
		:Task(name, data, imp, time), period(period) {}

	int get_period() const {       // выдача периода
		return period;
	}
	void print() const;
	void print_file(std::ofstream & file) const;
	
	Task_period* clone() const { return new Task_period(*this); }

	bool miss() {
		extension(period);
		return true;
	}

	bool change_period(int dper) {
		period = dper;
		return true;
	}

};
#endif