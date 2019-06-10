#ifndef TASK_H_
#define TASK_H_

#include <string>

class Task {

		std::string name; //!< строковый идентификатор задания
		std::string data; //!< текст задания
		int importance; //!< уровень важности задания
		int time; //!< временную метку крайнего срока исполнения задания (целое число, описывающее число секунд от некоторого фиксированного в рамках приложения момента в прошлом)
public:
		Task(const std::string& name, const std::string& data, int imp, int time)  //!< создание задания
			: name(name), data(data), importance(imp), time(time) {}

		int get_imp() const {        // выдача важности
			return importance;
		}

		int get_time() const {       // выдача времени
			return time;
		}

		const std::string& get_name(void) const{
			return name;
		}

		const std::string& get_data(void) const{
			return data;
     	}

		bool extension(int dtime) {     // продление времени
	
				
				if (((time+dtime) / 100000000) != 0) {
					 return false;
				}
				time += dtime;
				int day = (time % 100), month = ((time / 100) % 100), year = time / 10000;
				if (day > 28) 
				{
					if (month > 12) {
						year += 1;
						month -= 12;
					}
					if (month == 2 && year % 4 != 0)
					{
					    day -= 28;
						if (day > 31) {
							day -= 31;
							month += 2;
						}
						else month += 1;
					}
					else if (day>29 && month == 2 && year % 4 == 0) {
						day -= 29;
						if (day > 31) {
							day -= 31;
							month += 2;
						}
						else month += 1;
					}
					else if (day>30 && (month == 4 || month == 6 || month == 9 || month == 11))
					{
						day -= 30;
						if (day > 31) {
							day -= 31;
							month += 2;
						}
						else month += 1;
					}
					else if (day > 31 && month == 12)
					{
						day -= 31;
					    month = 1;
						year += 1;
					}
					else if(day>31) {
						day -= 31;
						month += 1;
					}
			
				}
				else if (month > 12) {
					year += 1;
					month -= 12;
				}
				time = (year* 10000)+ (month * 100) +day;
				return true;
		}

		void change_data(std::string ddata) {     // изменение важности
			
			data = ddata;
		}

		virtual bool miss() = 0;

		virtual bool change_period(int dper) = 0;

		bool change_imp(int dimp) {     // изменение важности
			if (dimp >= 0) {
				importance = dimp;
				return true;
			}
			else { return false; }
		}   

		void change_time(int dtime) {     // изменение времени
			
				time = dtime;
				return;
		}

		virtual void print() const =0;
		virtual void print_file(std::ofstream & file) const = 0;
		virtual Task* clone() const = 0;
		virtual ~Task() {}
		bool operator <(const Task &t) const {
			return time < t.time;
        }

		bool operator >(const Task &t) const {
			return time > t.time;
        }

		bool operator ==(const Task &t) const {
			return time == t.time;
		}

		bool operator >=(const Task &t) const {
			return time >= t.time;
		}
};
#endif