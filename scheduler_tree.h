#ifndef SCHEDULER_TREE_H_
#define SCHEDULER_TREE_H_

#include "task.h"
using std::string;

class Scheduler {
private:
	class Node {

	public:

		Task* task;
		Node* left = nullptr;
		Node* right = nullptr;
		bool is_left_thread = false;
		bool is_right_thread = false;


		Node(Task* task, Node* left = nullptr, Node* right = nullptr)
			: task(task), left(left), right(right) {}

		~Node() {
			delete task;
		}
	};

	Node * scheduler_top = nullptr;

	void add(Node*& scheduler_top, Task* task);
	void print(Node* scheduler_top);
	void search(Node* scheduler_top, const string& name_task, Task *& result_of_search);
	void search_to_delete(Node* scheduler_top, const string& name_task, Node *& result_of_search);
	void delete_all_tree(Node*& scheduler_top);
	void delete_one_node(Node *& task_to_delete);
public:

	void add(Task* task) {
		add(scheduler_top, task);
	};
	void show();
	void show_file(string name);

	void print() {
		print(scheduler_top);
	};
		
	void search(const string& name_task, Task *& result_of_search) {
		result_of_search = nullptr;
		search(scheduler_top, name_task, result_of_search);
	};
	
	void delete_all_tree() {
		delete_all_tree(scheduler_top);
	};
	void delete_one_task(const string& name_task);
	void perform(const string& name_task);
	void print_first();
	void print_first_file(string name);

	~Scheduler() {
		delete_all_tree();
	}
};
#endif
