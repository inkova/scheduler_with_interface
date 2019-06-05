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
			if ((time + dtime) >= 0) {
				time += dtime;
				return true;
			}
			else { return false; }
		}

		//bool extension(int dtime) {     // продление времени
		//	int next_day = 0, next_month=0, next_year = 0;
		//	
		//	next_day = (time %100)+ (dtime % 100);
		//	next_month = ((time / 100) % 100) + ((dtime / 100) % 100);
		//	next_year = (time / 10000)+ (dtime / 10000);
		//	if (*next_day >= 29 && *next_month == 2 && *next_year % 4 != 0)
		//	{
		//		next_day -= ;
		//		*next_month += 1;
		//	}
		//	if (*next_day == 31 && (*next_month == 4 || *next_month == 6 || *next_month == 9 || *next_month == 11))
		//	{
		//		*next_day = 1;
		//		*next_month += 1;
		//	}
		//	if (*next_day == 32)
		//	{
		//		if (*next_month == 12)
		//		{
		//			*next_day = 1;
		//			*next_month = 1;
		//			*next_year += 1;
		//		}
		//		else
		//		{
		//			*next_day = 1;
		//			*next_month += 1;
		//		}
		//	}
		//}



		virtual bool miss() = 0;

		bool change_imp(int dimp) {     // изменение важности
			if (dimp >= 0) {
				importance = dimp;
				return true;
			}
			else { return false; }
		}   
		virtual void print() const =0;
		//virtual void print_file(std::ofstream file) const = 0;
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
};
#endif