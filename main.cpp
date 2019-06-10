#include <cassert> 
#include <string>
#include <cstdlib>
#include <cctype> 
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <map>
#include <utility>
#include <vector>


#include "task_once.h" 
#include "task.h"
#include "task_period.h"
#include "scheduler_tree.h"
#include "sch_mode.h"



using std::multimap;
using std::pair;

using std::vector;
using std::shared_ptr;
using namespace std;
using std::string;
using std::endl;
using std::cout;
using std::cin;


int skip(int j, ifstream & file)
{
	int i;
	//char ch;
	for (i = 0; i < j; i++)
	{
		if (!file.eof()) {
			 file.get(); 
			//cout << ch;
		}
		else return 0;
	}
	return 1;
}


int answer_smaller(int max_num)
{
	string tmp;
	int i = 0, num=0;

	getline(cin, tmp);
	num = atoi(tmp.c_str());
	if (num == 0 || num < 0 || num > max_num)
	{
		tmp.clear();
		printf("Incorrect answer. Enter from 1 to %d\n", max_num);
		return 0;
	}
	tmp.clear();
	return num;

}

bool validation_check(int num, int max_num) {
	if (num == 0 || num < 0 || num > max_num)
	{
		return false;
	}
	return true;
}

bool get_int(int* num)
{
	string tmp;
	int i=0;

	getline(cin, tmp);
	while (tmp.empty()) {
		printf("\ninput DATA of task   ");
		getline(cin, tmp);
	}
	*num = atoi(tmp.c_str());
	if (*num == 0)
	{
		while (tmp[i] == ' ') i++;
		if (tmp[i] == '0') {
			tmp.clear();  
			return true;
		}
		else {
			tmp.clear(); 

			return false;
		}
	}
	if (*num < 0) {
		tmp.clear();
		return false;
	}
	tmp.clear();
	return true;
}

bool check_int(int num, string tmp) {
	int i = 0;
	if (num == 0)
	{
		while (tmp[i] == ' ') i++;
		if (tmp[i] == '0') {
			return true;
		}
		else {
			return false;
		}
	}
	if (num < 0) {
		
		return false;
	}
	return true;
}

int get_correct_day(int year, int month) {
	int day;
	if ( month == 2 && year % 4 != 0)
	{
		day = answer_smaller(28);
		while (!day) day = answer_smaller(28);
	}
	else if (month == 2 && year % 4 == 0) {
		day = answer_smaller(29);
		while (!day) day = answer_smaller(29);
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		day = answer_smaller(30);
		while (!day) day = answer_smaller(30);
	}
	else {
		day = answer_smaller(31);
		while (!day) day = answer_smaller(31);
	}
	return day;
}

int check_correct_day(int year, int month) {
	if (month == 2 && year % 4 != 0)
	{
		return 28;
	}
	else if (month == 2 && year % 4 == 0) {
		return 29;
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		return 30;
	}
	else {
		return 31;
	}
}

int input_time_period(int ch)
{
	int time = 0, for_time = 0;
	if(ch) printf("\nafter how many YEARS should the task be repeated?  ");
	else printf("\nfor how many YEARS should the deadline be extended?  ");
	while (!(get_int(&for_time)) || for_time > 9999) printf("Wrong input. Enter from 0 to 9999\n");
	time = for_time * 10000;

	if (ch) printf("\nafter how many MONTHS should the task be repeated?  ");
	else printf("\nfor how many MONTHS should the deadline be extended?  ");
	while (!(get_int(&for_time)) || for_time > 12) printf("Wrong input. Enter from 0 to 12\n");
	time += for_time * 100;

	if (ch) printf("\nafter how many DAYS should the task be repeated?  ");
	else printf("\nfor how many DAYS should the deadline be extended?  ");
	while (!(get_int(&for_time)) && for_time > 31) printf("Wrong input. Enter from 0 to 31\n");
	time += for_time;
	return time;
}




int input_time()
{
	int time=0, for_time = 0;
    printf("\nenter the YEAR of completion task  ");
	for_time = answer_smaller(9999);
	while (!for_time) for_time = answer_smaller(9999);
	time = for_time * 10000;

	printf("\nenter the MONTH of completion task  ");
	for_time = answer_smaller(12);
	while (!for_time) for_time = answer_smaller(12);
	time += for_time * 100;

    printf("\nenter the DAY of completion task  ");
	for_time = get_correct_day(time / 10000, for_time);
	time += for_time;
	return time;
}



/*void scheduler_mode() {
	Scheduler_mode  sch_m = Scheduler_mode();
	Sched * sched_p;

	multimap <int, string> mmTask1;
	vector<int>;
	string name;
	int selector, time_f = 0, time_f_tmp = 0, time_t = 0, time_t_tmp = 0;
	while (1)
	{
		printf("\n1)input task\n2)input task(s) from file\n3)show result\n4)print result to file\n5)exit to main menu\n\nWhat do you want to do?(enter the desired digit) : ");
		selector = answer_smaller(5);
		while (!selector)  selector = answer_smaller(5);
		printf("\n");
		switch (selector)
		{
		case 1: {
			printf("input task:\ninput NAME of task   ");
			name.clear();
			getline(cin, name);
			while (name.empty()) {
				printf("\ninput NAME of task   ");
				getline(cin, name);
			}

			printf("input BEGINNING of task\nHOUR   ");
			while (!(get_int(&time_f_tmp)) && time_f_tmp > 23) printf("Wrong input. Enter from 0 to 23\n");
			time_f = time_f_tmp * 60;
			time_f_tmp = 0;
			printf("\nMINUTE   ");
			while (!(get_int(&time_f_tmp)) && time_f_tmp > 59) printf("Wrong input. Enter from 0 to 59\n");
			time_f += time_f_tmp;

			printf("input END of task\nHOUR   ");
			while (!(get_int(&time_t_tmp)) && time_t_tmp > 23) printf("Wrong input. Enter from 0 to 23\n");
			time_t = time_t_tmp * 60;
			time_t_tmp = 0;
			printf("\nMINUTE   ");
			while (!(get_int(&time_t_tmp)) && time_t_tmp > 59) printf("Wrong input. Enter from 0 to 59\n");
			time_t += time_t_tmp;

			sched_p = new Sched(name, time_f, time_t);
			sch_m.insert(sched_p);
			break; }
		}
	}

*/
int scheduler_mode() {
	Scheduler_mode  sch_m = Scheduler_mode();
	Sched * sched_p;
	vector < shared_ptr<Sched>> result;
	vector < shared_ptr<Sched>> ::iterator res_it;

	string name, tmp;
	int selector, time_f = 0, time_f_tmp = 0, time_t = 0, time_t_tmp = 0;
	while (1)
	{
		printf("\n1)input task\n2)input task(s) from file\n3)show result\n4)print result to file\n5)generation of the maximum list of non-overlapping tasks\n6)print the maximum list of non-overlapping tasks\n7)print the maximum list of non-overlapping tasks to file\n8)delete task by name\n9)delete all base of tasks\n10)exit to main menu\n\nWhat do you want to do?(enter the desired digit) : ");

		selector = answer_smaller(10);
		while (!selector)  selector = answer_smaller(10);
		printf("\n");
		switch (selector)
		{
		case 1: {
			printf("input task:\ninput NAME of task   ");
			name.clear();
			getline(cin, name);
			while (name.empty()) {
				printf("\ninput NAME of task   ");
				getline(cin, name);
			}
			while (!(sch_m.check_name_mode(name))) {
				printf("Task with this name already exists.\n");
				printf("\nPlease enter another name.\n");
				getline(cin, name);
				while (name.empty()) {
					printf("\ninput NAME of task   ");
					getline(cin, name);
				}
			}

			do 
			{
				if (time_f_tmp) printf("\nThe beginning time of the task should not be longer than the end time of the task\n\n");
				printf("input BEGINNING of task\nHOUR   ");
				while (!(get_int(&time_f_tmp)) || time_f_tmp > 23) printf("Wrong input. Enter from 0 to 23\n");
				time_f = time_f_tmp * 60;
				time_f_tmp = 0;
				printf("\nMINUTE   ");
				while (!(get_int(&time_f_tmp)) || time_f_tmp > 59) printf("Wrong input. Enter from 0 to 59\n");
				time_f += time_f_tmp;

				printf("input END of task\nHOUR   ");
				while (!(get_int(&time_t_tmp)) || time_t_tmp > 23) printf("Wrong input. Enter from 0 to 23\n");
				time_t = time_t_tmp * 60;
				time_t_tmp = 0;
				printf("\nMINUTE   ");
				while (!(get_int(&time_t_tmp)) || time_t_tmp > 59) printf("Wrong input. Enter from 0 to 59\n");
				time_t += time_t_tmp;
				time_f_tmp = 1;
			} while (time_f > time_t);
			time_f_tmp = 0;
			sched_p = new Sched(name, time_f, time_t);
			sch_m.insert(sched_p);
			break;
		}
		case 2: {
			printf("\ninput name of file\n");
			name.clear();
			getline(cin, name);
			while (name.empty()) {
				printf("\ninput name of file\n");
				getline(cin, name);
			}
			std::ifstream file(name);
			if (!file) {
				cout << "File " << name << " can not be open.\n";
				getline(cin, tmp);
				break;
			}

			while (!file.eof()) {
				skip(15, file);
				name.clear();
				getline(file, name);

				if (!(sch_m.check_name_mode(name))) {
					cout << "Sorry, but an inaccuracy was found in the file provided for reading.\n"
					<< "Task with this name \"" << name << "\" already exists.\n";
					printf("Please enter another name.\nCorrect the error in the file or provide another file for reading.\n");
					getline(cin, tmp);
					break;
				}

				skip(17, file);
				tmp.clear();
				time_f = 0;
				getline(file, tmp, ':');
				time_f_tmp = atoi(tmp.c_str());
				if (!(check_int(time_f_tmp, tmp)) || time_f_tmp > 23) {
					cout << "Sorry, but an inaccuracy was found in the file provided for reading. The HOUR of beginning of task \"" << name << "\" should be from 1 to 23. Please correct the error in the file or provide another file for reading." << endl;
					getline(cin, tmp);
					break;
				}
				time_f = time_f_tmp * 60;


				tmp.clear();
				getline(file, tmp);
				time_f_tmp = atoi(tmp.c_str());
				if (!(check_int(time_f_tmp, tmp)) || time_f_tmp > 59) {
					cout << "Sorry, but an inaccuracy was found in the file provided for reading. The MINUTE of beginning of task \"" << name << "\" should be from 1 to 59. Please correct the error in the file or provide another file for reading." << endl;
					getline(cin, tmp);
					break;
				}
				time_f += time_f_tmp;

				skip(11, file);
				tmp.clear();
				time_t = 0;
				getline(file, tmp, ':');
				time_t_tmp = atoi(tmp.c_str());
				if (!(check_int(time_t_tmp, tmp)) || time_t_tmp > 23) {
					cout << "Sorry, but an inaccuracy was found in the file provided for reading. The HOUR of end of task \"" << name << "\" should be from 1 to 23. Please correct the error in the file or provide another file for reading." << endl;
					getline(cin, tmp);
					break;
				}
				time_t = time_t_tmp * 60;

				tmp.clear();
				getline(file, tmp);
				time_t_tmp = atoi(tmp.c_str());
				if (!(check_int(time_t_tmp, tmp)) || time_t_tmp > 59) {
					cout << "Sorry, but an inaccuracy was found in the file provided for reading. The MINUTE of end of task \"" << name << "\" should be from 1 to 59. Please correct the error in the file or provide another file for reading." << endl;
					break;
				}
				time_t += time_t_tmp;
				
				if (time_f > time_t) {
					cout <<"\nSorry, but an inaccuracy was found in the file provided for reading. The beginning time of the task \"" << name << "\" should not be longer than the end time of the task\n\n";
					getline(cin, tmp);
					break;
				}
				
				skip(1, file);
				sched_p = new Sched(name, time_f, time_t);
				sch_m.insert(sched_p);
			}
			printf("\nSuccessfully completed.\n");
			getline(cin, tmp);
			break;
		}

		case 3: {
			if (sch_m.empty()) {
				printf("\nSorry but the base of tasks is empty. Enter the tasks for which you want to calculate the maximum list of tasks.\n");
				getline(cin, tmp);
				break;
			}
			sch_m.show_sch();
			printf("\nSuccessfully completed.\n");
			getline(cin, tmp);
			break;
		}

		case 4: {
			if (sch_m.empty()) {
				printf("\nSorry but the base of tasks is empty.\n Enter the tasks for which you want to calculate the maximum list of tasks.\n");
				getline(cin, tmp);
				break;
			}
			printf("\ninput name of file\n");
			name.clear();
			getline(cin, name);
			while (name.empty()) {
				printf("\ninput name of file\n");
				getline(cin, name);
			}
			std::ofstream file(name);
			if (!file) {
				cout << "File " << name << " can not be open.\n";
				break;
			}
			sch_m.show_sch_file(file);
			printf("\nSuccessfully completed.\n");
			getline(cin, tmp);
			break;
		}

		case 5: {
			if (sch_m.empty()) {
				printf("\nSorry but the base of tasks is empty.\n Enter the tasks for which you want to calculate the maximum list of tasks.\n");
				getline(cin, tmp);
				break;
			}
			result.clear();
			sch_m.mode(result);
			printf("\nSuccessfully completed.\n");
			getline(cin, tmp);
			break;
		}
		case 6: {//печать информации в векторе
			if (result.empty()) {
				printf("\niSorry. The maximum list of non-overlapping tasks is empty. Perhaps you forgot to generate it.\n");
				getline(cin, tmp);
				break;
			}

			for (res_it = result.begin(); res_it != result.end(); res_it++) {

				res_it->get()->print();
			}
			getline(cin, tmp);
			break;
		}
		case 7: { //печать информации в векторе
			if (result.empty()) {
				printf("\nSorry. The maximum list of non-overlapping tasks is empty. Perhaps you forgot to generate it.\n");
				getline(cin, tmp);
				break;
			}
			printf("\ninput name of file\n");
			name.clear();
			getline(cin, name);
			while (name.empty()) {
				printf("\ninput name of file\n");
				getline(cin, name);
			}
			std::ofstream file(name);
			if (!file) {
				cout << "File " << name << " can not be open.\n";
				getline(cin, tmp);
				break;
			}

			for (res_it = result.begin(); res_it != result.end(); res_it++) {

				res_it->get()->print_file(file);
			}
			printf("\nSuccessfully completed.\n");
			getline(cin, tmp);
			break;
		}
		case 8: {
			if (sch_m.empty()) {
				printf("\nSorry but the base of tasks is empty.\n Enter the tasks for which you want to calculate the maximum list of tasks.\n");
				getline(cin, tmp);
				break;
			}
			printf("\ninput name of task\n");
			name.clear();
			getline(cin, name);
			while (name.empty()) {
				printf("\ninput name of task\n");
				getline(cin, name);
			}
			sch_m.delete_one_sch(name);
			printf("\nSuccessfully completed.\n");
			getline(cin, tmp);
			break;
		}
		case 9:{
			if (sch_m.empty()) {
				printf("\nSorry but the base of tasks is empty. Enter the tasks for which you want to calculate the maximum list of tasks.\n");
				getline(cin, tmp);
				break;
			}
			sch_m.clean();
			printf("\nSuccessfully completed.\n");
			getline(cin, tmp);
			break;
		}
		case 10: {
			result.clear();
			sch_m.clean();
			return 0;
			break;
		}
		}
	}
	return 8;
}



int main() {
	int selector, i;
	char ch;
	string name, data, tmp;
	int time = 0, importance = 0, period = 0, for_time=0;
	Task_once *to;
	Task_period *tp;
	Scheduler  sch = Scheduler();
	while (1)
	{
		printf("\nWelcome to the scheduler!\n\n1)input task\n2)input task(s) from file\n3)show database\n4)print database to file\n5)print task by name\n6)change data of task by name\n7)change importance by name\n8)change period of task by name\n9)change task execution time\n10)extend the deadline for the task\n11)print earliest task\n12)print the earliest task to file\n13)perform a task\n14)delete task by name\n15)delete all database\n16)scheduler mode\n17)Exit\n\nWhat do you want to do?(enter the desired digit) : ");
		selector = answer_smaller(17);
		while (!selector)  selector = answer_smaller(17); 
		printf("\n");
		switch (selector)
		{
		case 1: {
			printf("input task:\ninput NAME of task   ");
			name.clear();
			getline(cin, name);
			while (name.empty()) {
				printf("\ninput NAME of task   ");
				getline(cin, name);
			}
			Task * result_of_search = nullptr;
			sch.search(name, result_of_search);
			while (result_of_search != nullptr) {
				printf("Task with this name already exists.\n");
				result_of_search->print();
				printf("\nPlease enter another name.\n");
				getline(cin, name);
				while (name.empty()) {
					printf("\ninput NAME of task   ");
					getline(cin, name);
				}
				sch.search(name, result_of_search);
			}
			//			getline(cin, tmp);
			//			while (!tmp.empty()) {
			//				name += tmp;
			//				getline(cin, tmp);
			//			}
			//			cout << name << "\n";
			printf("\ninput DATA of task   ");
			data.clear();
			getline(cin, data);
			while (data.empty()) {
				printf("\ninput DATA of task   ");
				getline(cin, data);
			}

			printf("\ninput TIME of task\n ");
			time = input_time();

			printf("\ninput IMPORTANCE of task   ");
			while (!(get_int(&importance))) printf("Wrong input. Enter a positive integer or 0.");
			printf("\nIs task periodically?\n1)yes\n2)no\n");
			i = answer_smaller(2);
			while (!i) i = answer_smaller(2);
			if (i == 2) {
				to = new Task_once(name, data, importance, time);
				to->print();
				sch.add(to);
			}
			else {
				printf("\ninput PERIOD of task\n");
				period = input_time_period(1);
				tp = new Task_period(name, data, importance, time, period);
				tp->print();
				sch.add(tp);
			}
			printf("\nSuccessfully completed.\n");
			getline(cin, tmp);
			break; }

		case 2:{
			printf("\ninput name of file\n");
			name.clear();
			getline(cin, name);
			while (name.empty()) {
				printf("\ninput name of file\n");
				getline(cin, name);
			}
			ifstream file(name);
			if (!file) {
				cout << "File " << name << " can not be open.\n";
				getline(cin, tmp);
				break;
			}
			Task * result_of_search = nullptr;

			while (!file.eof()){
				ch = '\n';
				while (!file.eof() && !(isalpha(ch))) { ch = file.get(); 
				}
				if (file.eof()) break;
				skip(14, file);
				name.clear();
				getline(file, name);

				sch.search(name, result_of_search);
				if (result_of_search != nullptr) {
					cout << "\nSorry, but an inaccuracy was found in the file provided for reading.\n";
					cout<< "Task with this name \""<<name <<"\" already exists.\n";
					result_of_search->print();
					printf("\nPlease correct the error in the file or provide another file for reading.\n");
					getline(cin, tmp);
					break;
				}

				skip(10, file);
				data.clear();
				getline(file, data);
				
				skip(18, file);
				tmp.clear();
				getline(file, tmp);
				importance = atoi(tmp.c_str());
				if(!( check_int(importance, tmp) )) {
					cout << "\nSorry, but an inaccuracy was found in the file provided for reading.\n The IMPORTANCE of the task \"" << name << "\" should be a positive integer or 0. Please correct the error in the file or provide another file for reading." << endl;
					getline(cin, tmp);
					break;
				}

				skip(12, file);
				tmp.clear();
				time = 0;
				getline(file, tmp, '.');
				for_time = atoi(tmp.c_str());
				//printf(" %d ", for_time);
				time = for_time;
				

				tmp.clear();
				getline(file, tmp, '.');
				for_time = atoi(tmp.c_str());
				if (!(validation_check(for_time, 12))) {
					cout << "\nSorry, but an inaccuracy was found in the file provided for reading.\n The MONTH of the deadline for the task \"" << name << "\" should be from 1 to 12. Please correct the error in the file or provide another file for reading." << endl;
					getline(cin, tmp);
					break;
				}
				time += for_time * 100;
				//printf (" %d " ,for_time);

				tmp.clear();
				getline(file, tmp);
				for_time = atoi(tmp.c_str());
				if (!(validation_check(for_time, 9999))) {
					cout << "\nSorry, but an inaccuracy was found in the file provided for reading.\n The YEAR of the deadline for the task \"" << name << "\" should be from 1 to 9999. Please correct the error in the file or provide another file for reading." << endl;
					getline(cin, tmp);
					break;
				}
				time += for_time * 10000;
				//printf(" %d ", for_time);
				if (!(validation_check((time % 100), check_correct_day( (time / 10000), ((time / 100) % 100) ) ))) {
					cout << "\nSorry, but an inaccuracy was found in the file provided for reading.\n The DAY of the deadline for the task \"" << name << "\" should be from 1 to "<< check_correct_day((time / 10000), ((time / 100) % 100)) <<". Please correct the error in the file or provide another file for reading." << endl;
					getline(cin, tmp);
					break;
				}  

				//tmp.clear();
				//getline(file, tmp);
				//i = atoi(tmp.c_str());
				ch = file.get();
				//printf("| %c |", ch);
				if(!(ch=='I'))
				 {
					to = new Task_once(name, data, importance, time);
					//to->print();
					sch.add(to);
				}
				else {
					skip(13, file);
					tmp.clear();
					getline(file, tmp, ' ');
					for_time = atoi(tmp.c_str());
					if (!(check_int(for_time, tmp)) || for_time>31) {
						cout << "\nSorry, but an inaccuracy was found in the file provided for reading.\n The DAY of the period for the task \"" << name << "\" should be from 1 to 31. Please correct the error in the file or provide another file for reading." << endl;
						getline(cin, tmp);
						break;
					}
					period = for_time;

					skip(7, file);
					tmp.clear();
					getline(file, tmp, ' ');
					for_time = atoi(tmp.c_str());
					if (!(check_int(for_time, tmp)) || for_time > 12) {
						cout << "\nSorry, but an inaccuracy was found in the file provided for reading.\n The MONTH of the period for the task \"" << name << "\" should be from 1 to 12. Please correct the error in the file or provide another file for reading." << endl;
						getline(cin, tmp);
						break;
					}
					period += for_time * 100;

					skip(9, file);
					tmp.clear();
					getline(file, tmp);
					for_time = atoi(tmp.c_str());
					if (!(check_int(for_time, tmp)) || for_time > 9999) {
						cout << "\nSorry, but an inaccuracy was found in the file provided for reading.\n The YEAR of the period for the task \"" << name << "\" should be from 1 to 9999. Please correct the error in the file or provide another file for reading." << endl;
						getline(cin, tmp);
						break;
					}
					period += for_time * 10000;

					skip(1, file);

					tp = new Task_period(name, data, importance, time, period);
					//tp->print();
					sch.add(tp);
				}
			}
			//printf("\nSuccessfully completed.\n");
			getline(cin, tmp);
			break;}
		case 3: {
			printf("\nDatabase:\n");
			sch.show();
			printf("\nSuccessfully completed.\n");
			getline(cin, tmp);
			break; }
		case 4: {
			printf("\ninput name of file\n");
			name.clear();
			getline(cin, name);
			while (name.empty()) {
				printf("\ninput name of file\n");
				getline(cin, name);
			}
			sch.show_file(name);
			printf("\nSuccessfully completed.\n");
			getline(cin, tmp);
			break; }
		case 5: {
			printf("\ninput name of task to print\n");
			name.clear();
			getline(cin, name);
			while (name.empty()) {
				printf("\ninput name of task to print\n");
				getline(cin, name);
			}
			Task * result_of_search = nullptr;
			sch.search(name, result_of_search);
			if (result_of_search != nullptr) result_of_search->print();
			else {
				printf("Task with this name not found\n");
				getline(cin, tmp);
				break;
			}
			printf("\nSuccessfully completed.\n");
			getline(cin, tmp);
			break; }
		
		case 6: {
			printf("\ninput name of task\n");
			name.clear();
			getline(cin, name);
			while (name.empty()) {
				printf("\ninput name of task\n");
				getline(cin, name);
			}

			Task * result_of_search = nullptr;
			sch.search(name, result_of_search);
			if (result_of_search == nullptr) {
				printf("Task with this name not found\n");
				getline(cin, tmp);
				break;
			}
			printf("\ninput new data\n");
			data.clear();
			getline(cin, data);
			while (data.empty()) {
				printf("\ninput new data\n");
				getline(cin, data);
			}
			result_of_search->change_data(data);
			printf("\nSuccessfully completed.\n");
			getline(cin, tmp);
			break; }
		
		case 7: {
			printf("\ninput name of task\n");
			name.clear();
			getline(cin, name);
			while (name.empty()) {
				printf("\ninput name of task\n");
				getline(cin, name);
			}

			Task * result_of_search = nullptr;
			sch.search(name, result_of_search);
			if (result_of_search == nullptr) {
				printf("Task with this name not found\n");
				getline(cin, tmp);
				break;
			}
			printf("\ninput new importance\n");
			while (!(get_int(&i))) printf("Wrong input. Enter a positive integer or 0.");
			result_of_search->change_imp(i);
			printf("\nSuccessfully completed.\n");
			getline(cin, tmp);
			break; }
		case 8: {
			printf("\ninput name of task\n");
			name.clear();
			getline(cin, name);
			while (name.empty()) {
				printf("\ninput name of task\n");
				getline(cin, name);
			}

			Task * result_of_search = nullptr;
			sch.search(name, result_of_search);
			if (result_of_search == nullptr) {
				printf("Task with this name not found\n");
				getline(cin, tmp);
				break;
			}
			printf("\ninput new period\n");
			i = input_time_period(0);
			if (!(result_of_search->change_period(i))) printf("This task is not periodic, therefore its period cannot be changed.");

			printf("\nSuccessfully completed.\n");
			getline(cin, tmp);
			break; }
		case 9: {
			printf("\ninput name of task\n");
			name.clear();
			getline(cin, name);
			while (name.empty()) {
				printf("\ninput name of task\n");
				getline(cin, name);
			}

			Task * result_of_search = nullptr;
			sch.search(name, result_of_search);
			if (result_of_search == nullptr) {
				printf("Task with this name not found\n");
				getline(cin, tmp);
				break;
			}
			printf("\ninput new time\n");
			i = input_time();
			result_of_search->change_time(i);
			printf("\nSuccessfully completed.\n");
			getline(cin, tmp);
			break; }
		case 10: {
			printf("\ninput name of task\n");
			name.clear();
			getline(cin, name);
			while (name.empty()) {
				printf("\ninput name of task to extend\n");
				getline(cin, name);
			}
			Task * result_of_search = nullptr;
			sch.search(name, result_of_search);
			if (result_of_search == nullptr) {
				printf("Task with this name not found\n");
				getline(cin, tmp);
				break;
			}
			printf("\nenter how long do you want to extend\n");
			i = input_time_period(0);
			if (!(result_of_search->extension(i))) printf("\nThe deadline for completing the task cannot be extended.\n After the extension, the year becomes a five-digit number.\n The program only works over the years, which are four-digit numbers.\n");
			printf("\nSuccessfully completed.\n");
			getline(cin, tmp);
			break; }
		case 11: {
			sch.print_first();
			getline(cin, tmp);
			break; }
		case 12: {
			printf("\ninput name of file\n");
			name.clear();
			getline(cin, name);
			while (name.empty()) {
				printf("\ninput name of file\n");
				getline(cin, name);
			}
			sch.print_first_file(name);
			printf("\nSuccessfully completed.\n");
			getline(cin, tmp);
			break; }
		case 13: {
			printf("\ninput name of task\n");
			name.clear();
			getline(cin, name);
			while (name.empty()) {
				printf("\ninput name of task\n");
				getline(cin, name);
			}
			sch.perform(name);
			printf("\nSuccessfully completed.\n");
			getline(cin, tmp);
			break; }
		case 14: {
			printf("\ninput name of task to delete\n");
			name.clear();
			getline(cin, name);
			while (name.empty()) {
				printf("\ninput name of task to print\n");
				getline(cin, name);
			}
			sch.delete_one_task(name);
			printf("\nSuccessfully completed.\n");
			getline(cin, tmp);
			break; }
		case 15: {
			sch.delete_all_tree();
			printf("\nSuccessfully completed.\n");
			getline(cin, tmp);
			break; }
		
		case 16: {
			printf("Welcome to the scheduler mode.\n\nHere you can enter the name of the tasks, their beginning and end, and get a list of the maximum number of tasks that you can attend from the entered list without crossing the time.\n");
			scheduler_mode();
			break; }
		
		case 17: {sch.delete_all_tree(); return 0; break; }
	
	   }
	
	}
	return 0;
}
