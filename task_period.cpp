#include <iostream>
#include "task_period.h"
#include <fstream>

using std::ostream;
using std::endl;
using std::cout;

void Task_period::print() const {
	cout << "\nTask is called " << get_name() << "\nwith data " << get_data() 
		 << ".\nIts importance is " << get_imp() 
		 << ",\nits time is " << (get_time() % 100)<<"."<< ((get_time() / 100)% 100) << "." << (get_time() / 10000)
		 << "\nand its period is " << (get_period() % 100) << " day(s) " << ((get_period() / 100) % 100) << " month(s) " << (get_period() / 10000) <<" year(s)"
		 << endl;
}

void Task_period::print_file(std::ofstream &file) const {
	
	file << "Task is called " << get_name() << "\nwith data " << get_data()
		<< ".\nIts importance is " << get_imp()
		<< ",\nits time is " << (get_time() % 100) << "." << ((get_time() / 100) % 100) << "." << (get_time() / 10000)
		<< "\nand its period is " << (get_period() % 100) << " day(s) " << ((get_period() / 100) % 100) << " month(s) " << (get_period() / 10000) << " year(s)"
		<< endl;
}
