
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
		scheduler_top = new Node(task); // дерево пусто, значит добавляемый элемент - корень
	else

		if (*task < *(scheduler_top->task)) {    //необходимо перейти влево

			if (scheduler_top->left != nullptr && scheduler_top->is_left_thread == false) { // слево задание уже есть, сново проверять только с головой левого
				add(scheduler_top->left, task);
			}

			else {             // слево никого нет, помещаем сюда
				Node* for_prepering_to_add = new Node(task);
				//готовим левый конец
				if (scheduler_top->is_left_thread) {             //перекидываем прошивку
					for_prepering_to_add->left = scheduler_top->left;
					for_prepering_to_add->is_left_thread = true;
					scheduler_top->is_left_thread = false;
				}
				scheduler_top->left = for_prepering_to_add;

				for_prepering_to_add->right = scheduler_top;
				for_prepering_to_add->is_right_thread = true;
			}

		}

		else if (*(task) > *(scheduler_top->task)) {   // аналогично с левым

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
        while (scheduler_top->left != nullptr && scheduler_top->is_left_thread == false) { // переходим в самый левый лист
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
		while (scheduler_top->left != nullptr && scheduler_top->is_left_thread == false) { // переходим в самый левый лист
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
			while (scheduler_top->left != nullptr && scheduler_top->is_left_thread == false) { // переходим в самый левый лист
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

	 if (task_to_delete->left == nullptr && task_to_delete->right == nullptr) {   // только голова
		  delete task_to_delete;
		  task_to_delete = nullptr;
	 }

	else if ((task_to_delete->is_right_thread && (task_to_delete->left == nullptr)) ||   // если одна ветвь прошивка, а вторая пуста, 
             	(task_to_delete->is_left_thread && (task_to_delete->right == nullptr))) {  //то это крайний левый или крайний правый лист, его мы просто удаляем
		    
		    if (task_to_delete->is_right_thread) task_to_delete->right->left = nullptr;
			else task_to_delete->left->right = nullptr;
		    delete task_to_delete;
	     }

	else if (task_to_delete->is_left_thread && task_to_delete->is_right_thread) { //если обе ветви прошивки		

		if (task_to_delete->left->right == task_to_delete) {  //удаляемый это правая ветвь родителя
			
			task_to_delete->left->right = task_to_delete->right;  //перекидываем прошивку на родителя
			task_to_delete->left->is_right_thread = true;
			delete task_to_delete;
		}
		//удаляемый это левая ветвь родителя
		else { 

			task_to_delete->right->left = task_to_delete->left; //перекидываем прошивку на родителя
			task_to_delete->right->is_left_thread = true;
			delete task_to_delete;
		}
	}
	else if (task_to_delete->left != nullptr && !(task_to_delete->is_left_thread) && task_to_delete->is_right_thread) { // слева есть поддерево, справа только прошивка
		 tmp = task_to_delete->left;
		 while (tmp->is_right_thread == false) { // переходим в самый левый лист
			 tmp = tmp->right;
		 }
		 if (tmp->right == task_to_delete) {
			 tmp->right = task_to_delete->right;
		 }
		task_to_delete->right->left = task_to_delete->left;
		delete task_to_delete;
	}
	else if (task_to_delete->right != nullptr && !(task_to_delete->is_right_thread) && task_to_delete->is_left_thread) { // справа есть поддерево, слева только прошивка
		 tmp = task_to_delete->right;
		 while (tmp->is_left_thread == false) { // переходим в самый левый лист
			 tmp = tmp->left;
		 }
		 if (tmp->left==task_to_delete) {
			tmp->left = task_to_delete->left;
		 }
		task_to_delete->left->right = task_to_delete->right;
		delete task_to_delete;
	}

	else if (task_to_delete->left != nullptr && !(task_to_delete->is_left_thread) && task_to_delete->right == nullptr) { // слево поддерево, справо нулевой
		
		 if (task_to_delete->left->is_right_thread) {
			task_to_delete->left->right = nullptr;
			task_to_delete->left->is_right_thread = false;
		}
		tmp = task_to_delete;   //чтобы получить указатель на родителя, нужно пройти в самый левый лист поддерева, который и указывает чере прошивку на родителя
		while (tmp->is_left_thread == false) { // переходим в самый левый лист
			tmp = tmp->left;
		}

		tmp->left->right = task_to_delete->left;
		delete task_to_delete;
	}

	else if (task_to_delete->right != nullptr && !(task_to_delete->is_right_thread) && task_to_delete->left == nullptr) { // справо поддерево, слево нулевой
		if (task_to_delete->right->is_left_thread) {
			task_to_delete->right->left = nullptr;
			task_to_delete->right->is_left_thread = false;
		}
		tmp = task_to_delete;   //чтобы получить указатель на родителя, нужно пройти в самый правый лист поддерева, который и указывает через прошивку на родителя
		while (tmp->is_right_thread == false) { // переходим в самый правый лист
			tmp = tmp->right;
		}

		tmp->right->left = task_to_delete->right;
		delete task_to_delete;
	}
	else { //обе ветви имеют поддеревья, тогда замещаем удаляемый на самый левый правого поддерева	
		tmp = task_to_delete->right;
		while (tmp->is_left_thread == false) { // переходим в самый левый лист
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
		while (scheduler_top->left != nullptr && scheduler_top->is_left_thread == false) { // переходим в самый левый лист
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
		while (scheduler_top->left != nullptr && scheduler_top->is_left_thread == false) { // переходим в самый левый лист
			scheduler_top = scheduler_top->left;
		}

		scheduler_top->task->print_file(file);
	}
	file.close();
	return;
}
