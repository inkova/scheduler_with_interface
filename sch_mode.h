#ifndef SCH_MODE_H_
#define SCH_MODE_H_

#include "scheduler_mode_class.h"
#include <map>
#include <string>
#include <memory>
#include <utility>
#include <iostream>
#include <vector>

using std::multimap;
using std::shared_ptr;
using std::move;
using std::pair;       
using std::string;
using std::vector;


class Scheduler_mode {

private:
	
	multimap <int, shared_ptr<Sched>> mmSched;

public:

	void insert(Sched* sch_m_class)
	{
		mmSched.insert(make_pair(sch_m_class->get_time_to(), shared_ptr<Sched>(sch_m_class)));
	}

	void show_sch() {
		multimap <int, shared_ptr<Sched>> ::iterator it = mmSched.begin();
		for (; it != mmSched.end(); it++) {
			it->second->print();
		}
		return;
	}

	void show_sch_file(std::ofstream & file) {
		multimap <int, shared_ptr<Sched>> ::iterator it = mmSched.begin();
		for (; it != mmSched.end(); it++) {
			it->second->print_file(file);
		}
		return;
	}

	/*bool search(const string& name_task, multimap <int, shared_ptr<Sched>> ::iterator & it) {
		it = mmTask.begin();
		for (; it != mmSched.end(); it++) {
			if (it->second->get_name() == name_task) {
				return true;
			}
		}
		return false;
	}*/

	void clean() {
		mmSched.clear();
	};


	/*void delete_one_sch(const string& name_task) {

		multimap <int, shared_ptr<Sched>> ::iterator it = mmSched.end();
		if (!(search(name_task, it))) {
			cout << "\nTask with name " << name_task << " not found." << endl;
			return;
		}
		mmSched.erase(it);
		return;
	};*/

	void mode(vector < shared_ptr<Sched>> &result) {
		multimap <int, shared_ptr<Sched>> ::iterator  it, it_tmp;
		it = mmSched.begin();
		result.push_back(it->second);
		
		while (1) {
			it_tmp = it;
			it++;
			if (it == mmSched.end()) return;
			while (it->second.get()->get_time_from() < it_tmp->first) {

				it++;
				if (it == mmSched.end()) return;
			}
				//(it->second->get_time_from() < it_tmp->first) &&
				//	if (it == mmSched.end()) return;
				result.push_back(it->second);
			
		}
	}
};

#endif