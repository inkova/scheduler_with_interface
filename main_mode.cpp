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

#include "sch_mode.h"


using std::multimap;
using std::pair;
using std::string;
using std::vector;
using std::shared_ptr;
using std::cin;



int skip(int j, std::ifstream & file)
{
	int i;
	char ch;
	for (i = 0; i < j; i++)
	{
		if (!file.eof()) {
			ch = file.get(); printf("%c\n", ch);
		}
		else return 0;
	}
	return 1;
}

bool get_int(int* num)
{
	string tmp;
	int i = 0;

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
int answer_smaller(int max_num)
{
	string tmp;
	int i = 0, num = 0;

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


int main() {
	Scheduler_mode  sch_m = Scheduler_mode();
	Sched * sched_p;
	vector < shared_ptr<Sched>> result;
	vector < shared_ptr<Sched>> ::iterator res_it;
	//multimap <int, > mmTask1;
	//vector<int>;
	string name,tmp;
	int selector, time_f = 0, time_f_tmp = 0, time_t = 0, time_t_tmp = 0;
	while (1)
	{
		printf("\n1)input task\n2)input task(s) from file\n3)show result\n4)print result to file\n5)exit to main menu\n\nWhat do you want to do?(enter the desired digit) : ");

		selector = answer_smaller(7);
		while (!selector)  selector = answer_smaller(7);
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
				break;
			}

			while (!file.eof()) {
				skip(15, file);
				name.clear();
				getline(file, name);

				skip(17, file);
				tmp.clear();
				time_f = 0;
				getline(file, tmp, ':');
				time_f_tmp = atoi(tmp.c_str());
				time_f = time_f_tmp*60;
				printf("\n%d gg\n", time_f_tmp);

				tmp.clear();
				getline(file, tmp);
				time_f_tmp = atoi(tmp.c_str());
				time_f += time_f_tmp;

				skip(11, file);
				tmp.clear();
				time_t = 0;
				getline(file, tmp, ':');
				time_t_tmp = atoi(tmp.c_str());
				time_t = time_t_tmp * 60;
				printf("\n%d gg\n", time_f_tmp);

				tmp.clear();
				getline(file, tmp);
				time_t_tmp = atoi(tmp.c_str());
				time_t += time_t_tmp;
				skip(1, file);
				sched_p = new Sched(name, time_f, time_t);
				sch_m.insert(sched_p);
			}
			break;
		}
		
		case 3: {
			sch_m.show_sch();
			break;
		}

		case 4: {
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
			break;
		}

		case 5: {
			result.clear();
			sch_m.mode(result);
			for (res_it = result.begin(); res_it != result.end(); res_it++) {

				res_it->get()->print();
			}
			break;
		}
		case 6: {
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
			result.clear();
			sch_m.mode(result);
			for (res_it = result.begin(); res_it != result.end(); res_it++) {

				res_it->get()->print_file(file);
			}
			break;
		}
		case 7: {
			result.clear();
			return 0;
			break;
		}
		}
	}
	return 8;
}
