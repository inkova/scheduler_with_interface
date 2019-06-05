#ifndef TASK_ONCE_H_
#define TASK_ONCE_H_ //! �������� ������� ������������ ��������

#include <string>
#include"task.h"

class Task_once : public Task {
public:
	Task_once(const std::string& name, const std::string& data, int imp, int time)  //!< �������� �������
		:Task(name, data, imp, time) {}

	void print() const;
	//void print_file(std::ofstream file) const;
	Task_once* clone() const { return new Task_once(*this); }

	bool miss() {
		return false;
	}

};

#endif


