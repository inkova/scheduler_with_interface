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

int er_answer(int max_num)
{
	char letter;
	int answer;
	char letter_string[2], *i;
	i = letter_string;
	scanf_s("%c", &letter, 1);
	while (letter == ' ' && letter != '\n') scanf_s("%c", &letter, 1);

	if (isdigit(letter))
	{
		*i = letter;
		i++;
		*i = '\0';

		answer = atoi(letter_string);
		if ((answer) < (max_num + 1) && (answer) > 0) {
			scanf_s("%c", &letter, 1);

			while (letter == ' ') scanf_s("%c", &letter, 1);

			if (letter == '\n') return answer;
			else
			{
				printf("Incorrect answer. Enter from 1 to %d\n", max_num);
				while (letter != '\n') scanf_s("%c", &letter, 1);
				return 0;
			}

		}
		else {
			printf("Incorrect answer. Enter from 1 to %d\n", max_num);
			while (letter != '\n') scanf_s("%c", &letter, 1);
			return 0;
		}
	}
	else
	{
		printf("Incorrect answer.Enter from 1 to %d\n", max_num);
		while (letter != '\n') scanf_s("%c", &letter, 1);
		return 0;
	}
	return 0;

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

int input_time(int ch)
{
	int time=0, for_time = 0;
	if(ch) printf("\nenter the YEAR of completion task  ");
	else printf("\nafter how many YEARS should the task be repeated?  ");
	for_time = answer_smaller(9999);
	while (!for_time) for_time = answer_smaller(9999);
	time = for_time * 10000;

	if (ch)printf("\nenter the MONTH of completion task  ");
	else printf("\nafter how many MONTHS should the task be repeated?  ");
	for_time = answer_smaller(12);
	while (!for_time) for_time = answer_smaller(12);
	time += for_time * 100;

	if (ch)printf("\nenter the DAY of completion task  ");
	else printf("\nafter how many DAYS should the task be repeated?  ");
	for_time = get_correct_day(time / 10000, for_time);
	time += for_time;
	return time;
}

int main() {
	int selector, i;
	string name, data, tmp;
	int time = 0, importance = 0, period = 0, for_time=0;
	Task_once *to;
	Task_period *tp;
	Scheduler  sch = Scheduler();
	while (1)
	{
		printf("\nWelcome to the scheduler!\n\n1)input task\n2)input task(s) from file\n3)show database\n4)print task by name\n5)delete task by name\n6)delete all database\n7)change importance by name\n8)print earliest task\n9)Exit\n\nWhat do you want to do?(enter the desired digit) : ");
		selector = answer_smaller(9);
		while (!selector)  selector = answer_smaller(9); 
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
			time = input_time(1);

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
				period = input_time(0);
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
				printf("\n22input name of file\n");
				getline(cin, name);
			}
			ifstream file(name);
			if (!file) {
				cout << "File " << name << " can not be open.\n";
				break;
			}
			name.clear();
			while (getline(file, name)) {
				data.clear();
				getline(file, data);
				
				tmp.clear();
				time = 0;
				getline(file, tmp, '.');
				for_time = atoi(tmp.c_str());
				time = for_time;

				tmp.clear();
				getline(file, tmp, '.');
				for_time = atoi(tmp.c_str());
				time += for_time * 100;

				tmp.clear();
				getline(file, tmp);
				for_time = atoi(tmp.c_str());
				time += for_time * 10000;

			    tmp.clear();
				getline(file, tmp);
				importance = atoi(tmp.c_str());

				tmp.clear();
				getline(file, tmp);
				i = atoi(tmp.c_str());
				if (i == 2) {
					to = new Task_once(name, data, importance, time);
					//to->print();
					sch.add(to);
				}
				else {
					tmp.clear();
					getline(file, tmp, '.');
					for_time = atoi(tmp.c_str());
					period = for_time;

					tmp.clear();
					getline(file, tmp, '.');
					for_time = atoi(tmp.c_str());
					period += for_time * 100;

					tmp.clear();
					getline(file, tmp);
					for_time = atoi(tmp.c_str());
					period += for_time * 10000;
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
		/*case 11: {
			printf("\ninput name of file\n");
			name.clear();
			getline(cin, name);
			while (name.empty()) {
				printf("\n22input name of file\n");
				getline(cin, name);
			}
			sch.show_file(name);
			break; }*/
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


		/*case 5: {
			printf("\ninput name of task\n");
			name.clear();
			getline(cin, name);
			while (name.empty()) {
				printf("\ninput name of task to print\n");
				getline(cin, name);
			}
			printf("\nenter how long do you want to extend\n");
			while (!(get_int(&i))) printf("Wrong input. Enter a positive integer or 0.");
			Task * result_of_search = nullptr;
			sch.search(name, result_of_search);
			if (result_of_search != nullptr) result_of_search->extension(i);
			else printf("Task with this name not found\n");
			break; }*/
		
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
		case 9: { return 0; break; }
		
	   }
	
	}
	return 0;
}
