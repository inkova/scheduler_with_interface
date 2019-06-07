#include <iostream>
#include "task_once.h"
#include <fstream>
using std::endl;
using std::cout;
using std::ostream;

void Task_once::print() const {
	cout << "\nTask is called " << get_name() << "\nwith data " << get_data() 
		<< "\nIts importance is " << get_imp() 
		<< "\nIts time is " << (get_time() % 100) << "." << ((get_time() / 100) % 100) << "." << (get_time() / 10000) << endl;
}

void Task_once::print_file(std:: ofstream & file) const {
	
	file << "Task is called " << get_name() << "\nwith data " << get_data()
		<< "\nIts importance is " << get_imp()
		<< "\nIts time is " << (get_time() % 100) << "." << ((get_time() / 100) % 100) << "." << (get_time() / 10000) << endl << endl;
	
}
