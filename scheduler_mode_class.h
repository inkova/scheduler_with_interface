#ifndef SCHEDULER_MODE_CLASS_H_
#define SCHEDULER_MODE_CLASS_H_

#include <string>
#include <iomanip>
#include <iostream>
using std::endl;
using std::cout;

class Sched {

	std::string name; //!< строковый идентификатор задания
	int time_from;
	int time_to;
public:
	Sched(const std::string& name, int time_from, int time_to)  //!< создание задания
		: name(name), time_from(time_from), time_to(time_to) {}

	int get_time_from() const {       // выдача времени
		return time_from;
	};

	int get_time_to() const {       // выдача времени
		return time_to;
	};

	const std::string& get_name(void) const {
		return name;
	};

	void print() const {
		
		cout << "\nTask is called " << get_name();
		printf("\nits beginning is %02d:%02d\nits end is %02d:%02d\n", (get_time_from() / 60), (get_time_from() % 60), (get_time_to() / 60), (get_time_to() % 60));
	};

	void print_file(std::ofstream & file) const {

		file << "Task is called " << get_name()
		<< "\nits beginning is " << std::setfill('0') << std::setw(2) << (get_time_from() / 60) <<":"<< std::setfill('0') << std::setw(2) << (get_time_from() % 60)
		<< "\nits end is " << std::setfill('0') << std::setw(2) << (get_time_to() / 60) << ":" << std::setfill('0') << std::setw(2) << (get_time_to() % 60) 
			<< endl << endl;
	};
};
#endif