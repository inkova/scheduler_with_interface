#include <cassert> 
#include <string>
#include <cstdlib>
#include <cctype> 
#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;
using std::string;
using std::endl;
using std::cout;
using std::cin;

#include "task_once.h" 
#include "task.h"
#include "task_period.h"
#include "scheduler_tree.h"

int skip(int j, ifstream & file)
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
		printf("\nWelcome to the scheduler!\n\n1)input task\n2)input task(s) from file\n3)show database\n4)print task by name\n5)delete task by name\n6)delete all database\n7)change importance by name\n8)print earliest task\n9)Exit\n\nWhat do you want to do?(enter the desired digit) : ");
		selector = answer_smaller(13);
		while (!selector)  selector = answer_smaller(13); 
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
				break;
			}
			
			while (!file.eof()){
				skip(15, file);
				name.clear();
				getline(file, name);
				skip(10, file);
				data.clear();
				getline(file, data);
				
				skip(18, file);
				tmp.clear();
				getline(file, tmp);
				importance = atoi(tmp.c_str());

				skip(12, file);
				tmp.clear();
				time = 0;
				getline(file, tmp, '.');
				for_time = atoi(tmp.c_str());
				time = for_time;
				printf("%d\n", time);

				tmp.clear();
				getline(file, tmp, '.');
				for_time = atoi(tmp.c_str());
				time += for_time * 100;

				tmp.clear();
				getline(file, tmp);
				for_time = atoi(tmp.c_str());
				time += for_time * 10000;

				//tmp.clear();
				//getline(file, tmp);
				//i = atoi(tmp.c_str());
				ch = file.get();
				if(ch=='\n')
				 {
					printf("aaa");
					to = new Task_once(name, data, importance, time);
					//to->print();
					sch.add(to);
				}
				else {
					printf("bb");
					skip(17, file);
					tmp.clear();
					getline(file, tmp, ' ');
					for_time = atoi(tmp.c_str());
					period = for_time;

					skip(7, file);
					tmp.clear();
					getline(file, tmp, ' ');
					for_time = atoi(tmp.c_str());
					period += for_time * 100;

					skip(9, file);
					tmp.clear();
					getline(file, tmp);
					for_time = atoi(tmp.c_str());
					period += for_time * 10000;
					skip(8, file);
					tp = new Task_period(name, data, importance, time, period);
					//tp->print();
					sch.add(tp);
				}
			}
			break;}
		case 3: {
			printf("\nDatabase:\n");
			sch.show();
			break; }
		case 11: {
			printf("\ninput name of file\n");
			name.clear();
			getline(cin, name);
			while (name.empty()) {
				printf("\ninput name of file\n");
				getline(cin, name);
			}
			sch.show_file(name);
			break; }
		case 6: {
			sch.delete_all_tree();
			break; }
		case 5: {
			printf("\ninput name of task to delete\n");
			name.clear();
			getline(cin, name);
			while (name.empty()) {
				printf("\ninput name of task to print\n");
				getline(cin, name);
			}
			sch.delete_one_task(name);
			break; }
		case 4: {
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
			else printf("Task with this name not found\n");
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
				break;
			}
			printf("\nenter how long do you want to extend\n");
			i = input_time_period(0);
			if(!(result_of_search->extension(i))) printf("\nThe deadline for completing the task cannot be extended. After the extension, the year becomes a five-digit number. The program only works over the years, which are four-digit numbers.\n");
			break; }

		case 12: {
			printf("\ninput name of task\n");
			name.clear();
			getline(cin, name);
			while (name.empty()) {
				printf("\ninput name of task to extend\n");
				getline(cin, name);
			}
			sch.perform(name);
			break; }

		case 7: {
			printf("\ninput name of task\n");
			name.clear();
			getline(cin, name);
			while (name.empty()) {
				printf("\ninput name of task to print\n");
				getline(cin, name);
			}
			printf("\ninput new importance\n");
			while (!(get_int(&i))) printf("Wrong input. Enter a positive integer or 0.");
			Task * result_of_search = nullptr;
			sch.search(name, result_of_search);
			if (result_of_search != nullptr) result_of_search->change_imp(i);
			else printf("Task with this name not found\n");
			break; }
		case 8: {
			sch.print_first();
			break; }
		case 13: {
			printf("\ninput name of file\n");
			name.clear();
			getline(cin, name);
			while (name.empty()) {
				printf("\ninput name of file\n");
				getline(cin, name);
			}
			sch.print_first_file(name);
			break; }
		case 9: { return 0; break; }
		
	   }
	
	}
	return 0;
}
