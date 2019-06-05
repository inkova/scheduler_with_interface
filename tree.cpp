
#include <iostream>
#include "scheduler_tree.h"
#include "task.h"
#include "task_period.h"
#include "task_once.h"
#include <fstream>

using namespace std;
using std::string;
using std::endl;
using std::cout;

void Scheduler::add (Node*& scheduler_top, Task* task) {

	if (scheduler_top == nullptr)
		scheduler_top = new Node(task); // ������ �����, ������ ����������� ������� - ������
	else

		if (*task < *(scheduler_top->task)) {    //���������� ������� �����

			if (scheduler_top->left != nullptr && scheduler_top->is_left_thread == false) { // ����� ������� ��� ����, ����� ��������� ������ � ������� ������
				add(scheduler_top->left, task);
			}

			else {             // ����� ������ ���, �������� ����
				Node* for_prepering_to_add = new Node(task);
				//������� ����� �����
				if (scheduler_top->is_left_thread) {             //������������ ��������
					for_prepering_to_add->left = scheduler_top->left;
					for_prepering_to_add->is_left_thread = true;
					scheduler_top->is_left_thread = false;
				}
				scheduler_top->left = for_prepering_to_add;

				for_prepering_to_add->right = scheduler_top;
				for_prepering_to_add->is_right_thread = true;
			}

		}

		else if (*(task) > *(scheduler_top->task)) {   // ���������� � �����

			if (scheduler_top->right != nullptr && scheduler_top->is_right_thread == false)
				add(scheduler_top->right, task);

			else {

				Node* for_prepering_to_add = new Node(task);

				if (scheduler_top->is_right_thread) {
					for_prepering_to_add->right = scheduler_top->right;
					for_prepering_to_add->is_right_thread = true;
					scheduler_top->is_right_thread = false;
				}
				scheduler_top->right = for_prepering_to_add;

				for_prepering_to_add->left = scheduler_top;
				for_prepering_to_add->is_left_thread = true;

			}

		}
}

void Scheduler::show () {
	Node* scheduler_top = this->scheduler_top;
	if (scheduler_top == nullptr) {
		cout << "\nThere are no tasks in the scheduler.\n";
		return;
	}
    else while(1)
    {
        while (scheduler_top->left != nullptr && scheduler_top->is_left_thread == false) { // ��������� � ����� ����� ����
				scheduler_top= scheduler_top->left;
			}

              scheduler_top->task->print();        
              while(scheduler_top->is_right_thread == true){
                    scheduler_top = scheduler_top->right;
                    scheduler_top->task->print();
               }
               if(scheduler_top->right!=nullptr)
                scheduler_top=scheduler_top->right;
               else return;
    }
}

void Scheduler::show_file(std::string name) {
	Node* scheduler_top = this->scheduler_top;
	ofstream file(name);
	if (!file) {
		cout << "File " << name << " can not be open.\n";
		return;
	}

	if (scheduler_top == nullptr) {
		cout << "\nThere are no tasks in the scheduler.\n";
		file.close();
		return;
	}
	else while (1)
	{
		while (scheduler_top->left != nullptr && scheduler_top->is_left_thread == false) { // ��������� � ����� ����� ����
			scheduler_top = scheduler_top->left;
		}

		scheduler_top->task->print_file(file);
		while (scheduler_top->is_right_thread == true) {
			scheduler_top = scheduler_top->right;
			scheduler_top->task->print_file(file);
		}
		if (scheduler_top->right != nullptr)
			scheduler_top = scheduler_top->right;
		else {
			file.close();
			return;
		}
	}
}

//void Scheduler::print_file(Node* scheduler_top, std::ofstream file) {
//	if (scheduler_top == nullptr)
//	{	
//		return;
//	}
//	// printf("left: %i right: %i left pointer: %i right pointer: %i time: %i\n",
//   //	 scheduler_top->is_left_thread, scheduler_top->is_right_thread, scheduler_top->left, scheduler_top->right, scheduler_top->task->get_time());
//	if (!scheduler_top->is_left_thread)
//		print(scheduler_top->left);
//	scheduler_top->task->print_file(file);
//	if (!scheduler_top->is_right_thread)
//		print(scheduler_top->right);
//}

void Scheduler::print (Node* scheduler_top) {
	if(scheduler_top == nullptr)
    return;
 // printf("left: %i right: %i left pointer: %i right pointer: %i time: %i\n",
//	 scheduler_top->is_left_thread, scheduler_top->is_right_thread, scheduler_top->left, scheduler_top->right, scheduler_top->task->get_time());
  if(!scheduler_top->is_left_thread)
    print(scheduler_top->left);
  scheduler_top->task->print();
  if(!scheduler_top->is_right_thread)
    print(scheduler_top->right);
}

void Scheduler::search (Node* scheduler_top, const string& name_task, Task *& result_of_search) {
	
	if (scheduler_top == nullptr)
		return;
//	 printf("left: %i right: %i left pointer: %i right pointer: %i time: %i\n",
//  	 scheduler_top->is_left_thread, scheduler_top->is_right_thread, scheduler_top->left, scheduler_top->right, scheduler_top->task->get_time());
	if (scheduler_top->task->get_name() == name_task) {
		result_of_search = scheduler_top->task;
		return;
	}
	if (!scheduler_top->is_left_thread)
		search(scheduler_top->left, name_task, result_of_search);
	if (!scheduler_top->is_right_thread)
		search(scheduler_top->right, name_task, result_of_search);
}

void Scheduler::search_to_delete(Node* scheduler_top, const string& name_task, Node *& result_of_search_to_delete) {

	if (scheduler_top == nullptr)
		return;
	//	 printf("left: %i right: %i left pointer: %i right pointer: %i time: %i\n",
	//  	 scheduler_top->is_left_thread, scheduler_top->is_right_thread, scheduler_top->left, scheduler_top->right, scheduler_top->task->get_time());
	if (scheduler_top->task->get_name() == name_task) {
		result_of_search_to_delete = scheduler_top;
		return;
	}
	if (!scheduler_top->is_left_thread)
		search_to_delete(scheduler_top->left, name_task, result_of_search_to_delete);
	if (!scheduler_top->is_right_thread)
		search_to_delete(scheduler_top->right, name_task, result_of_search_to_delete);
}

void Scheduler:: delete_all_tree (Node*& scheduler_top) {

	Node * tmp = nullptr;
	if (scheduler_top == nullptr) return;
	else
		while (1)
		{
			while (scheduler_top->left != nullptr && scheduler_top->is_left_thread == false) { // ��������� � ����� ����� ����
				scheduler_top = scheduler_top->left;
			}
			while (scheduler_top->is_right_thread == true) {
				tmp = scheduler_top->right;
				delete scheduler_top;
				scheduler_top = tmp;
			}
			if (scheduler_top->right != nullptr) {
				tmp = scheduler_top->right;
				delete scheduler_top;
				scheduler_top = tmp;
			}
			else {
				delete scheduler_top;
				scheduler_top = nullptr;
				//cout << "\nComplete tree removal is finished.\n";
				return;
			}
		}
}

void Scheduler::delete_one_task(const string& name_task) {
	Node * task_to_delete = nullptr;
	Node* scheduler_top = this->scheduler_top;

	search_to_delete(scheduler_top, name_task, task_to_delete);
	if (task_to_delete == nullptr) {
		cout << "\nTask with name " << name_task << " not found." << endl;
		return;
	}
	delete_one_node(task_to_delete);
}

void  Scheduler::delete_one_node(Node *& task_to_delete){
	Node* tmp = nullptr;

	 if (task_to_delete->left == nullptr && task_to_delete->right == nullptr) {   // ������ ������
		  delete task_to_delete;
		  task_to_delete = nullptr;
	 }

	else if ((task_to_delete->is_right_thread && (task_to_delete->left == nullptr)) ||   // ���� ���� ����� ��������, � ������ �����, 
             	(task_to_delete->is_left_thread && (task_to_delete->right == nullptr))) {  //�� ��� ������� ����� ��� ������� ������ ����, ��� �� ������ �������
		    
		    if (task_to_delete->is_right_thread) task_to_delete->right->left = nullptr;
			else task_to_delete->left->right = nullptr;
		    delete task_to_delete;
	     }

	else if (task_to_delete->is_left_thread && task_to_delete->is_right_thread) { //���� ��� ����� ��������		

		if (task_to_delete->left->right == task_to_delete) {  //��������� ��� ������ ����� ��������
			
			task_to_delete->left->right = task_to_delete->right;  //������������ �������� �� ��������
			task_to_delete->left->is_right_thread = true;
			delete task_to_delete;
		}
		//��������� ��� ����� ����� ��������
		else { 

			task_to_delete->right->left = task_to_delete->left; //������������ �������� �� ��������
			task_to_delete->right->is_left_thread = true;
			delete task_to_delete;
		}
	}
	else if (task_to_delete->left != nullptr && !(task_to_delete->is_left_thread) && task_to_delete->is_right_thread) { // ����� ���� ���������, ������ ������ ��������
		 tmp = task_to_delete->left;
		 while (tmp->is_right_thread == false) { // ��������� � ����� ����� ����
			 tmp = tmp->right;
		 }
		 if (tmp->right == task_to_delete) {
			 tmp->right = task_to_delete->right;
		 }
		task_to_delete->right->left = task_to_delete->left;
		delete task_to_delete;
	}
	else if (task_to_delete->right != nullptr && !(task_to_delete->is_right_thread) && task_to_delete->is_left_thread) { // ������ ���� ���������, ����� ������ ��������
		 tmp = task_to_delete->right;
		 while (tmp->is_left_thread == false) { // ��������� � ����� ����� ����
			 tmp = tmp->left;
		 }
		 if (tmp->left==task_to_delete) {
			tmp->left = task_to_delete->left;
		 }
		task_to_delete->left->right = task_to_delete->right;
		delete task_to_delete;
	}

	else if (task_to_delete->left != nullptr && !(task_to_delete->is_left_thread) && task_to_delete->right == nullptr) { // ����� ���������, ������ �������
		
		 if (task_to_delete->left->is_right_thread) {
			task_to_delete->left->right = nullptr;
			task_to_delete->left->is_right_thread = false;
		}
		tmp = task_to_delete;   //����� �������� ��������� �� ��������, ����� ������ � ����� ����� ���� ���������, ������� � ��������� ���� �������� �� ��������
		while (tmp->is_left_thread == false) { // ��������� � ����� ����� ����
			tmp = tmp->left;
		}

		tmp->left->right = task_to_delete->left;
		delete task_to_delete;
	}

	else if (task_to_delete->right != nullptr && !(task_to_delete->is_right_thread) && task_to_delete->left == nullptr) { // ������ ���������, ����� �������
		if (task_to_delete->right->is_left_thread) {
			task_to_delete->right->left = nullptr;
			task_to_delete->right->is_left_thread = false;
		}
		tmp = task_to_delete;   //����� �������� ��������� �� ��������, ����� ������ � ����� ������ ���� ���������, ������� � ��������� ����� �������� �� ��������
		while (tmp->is_right_thread == false) { // ��������� � ����� ������ ����
			tmp = tmp->right;
		}

		tmp->right->left = task_to_delete->right;
		delete task_to_delete;
	}
	else { //��� ����� ����� ����������, ����� �������� ��������� �� ����� ����� ������� ���������	
		tmp = task_to_delete->right;
		while (tmp->is_left_thread == false) { // ��������� � ����� ����� ����
			tmp = tmp->left;
		}
		delete task_to_delete->task;
		task_to_delete->task = tmp->task->clone();
		delete_one_node (tmp);
	}
	return;
}

void Scheduler::perform(const string& name_task) {
	Task * result_of_search = nullptr, *tmp = nullptr;
	bool check=false;
	
	search(name_task, result_of_search);
	if (result_of_search != nullptr) {
		cout << "\nCompleted task:\n";
		result_of_search->print();
	}
	else {
		cout << "\nTask with name " << name_task << " not found." << endl;
		return;
	}

	tmp = result_of_search->clone();
	check= tmp->miss();
	delete_one_task(name_task);
	if(check) add(tmp);
        else  delete tmp;
	
	return;
}

void Scheduler::print_first() {
	Node* scheduler_top = this->scheduler_top;

	if (scheduler_top == nullptr) {
		cout << "\nThere are no tasks in the scheduler.\n";
		return;
	}
	else 
	{
		while (scheduler_top->left != nullptr && scheduler_top->is_left_thread == false) { // ��������� � ����� ����� ����
			scheduler_top = scheduler_top->left;
		}

		scheduler_top->task->print();
	}
	return;
}

void Scheduler::print_first_file(std::string name) {
	Node* scheduler_top = this->scheduler_top;
	ofstream file(name);
	if (!file) {
		cout << "File " << name << " can not be open.\n";
		return;
	}

	if (scheduler_top == nullptr) {
		cout << "\nThere are no tasks in the scheduler.\n";
		return;
	}
	else
	{
		while (scheduler_top->left != nullptr && scheduler_top->is_left_thread == false) { // ��������� � ����� ����� ����
			scheduler_top = scheduler_top->left;
		}

		scheduler_top->task->print_file(file);
	}
	file.close();
	return;
}
