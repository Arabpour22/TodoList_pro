// 4032226225
// 4031226147
#include <iostream> 
#include <string>
#include <vector>  
#include <ctime>

using namespace std;

class Task {
	
protected:
    string title;
    string description;
    bool done;
    time_t createDate;
    time_t deadline;
    string priority;

public:
    Task(string t, string d, time_t dl, string p):title(t),description(d),deadline(dl),priority(p) {
        done = false;
        createDate = time(0);
    }

    void toggleDone() {
        done = !done;
    }

    bool isOverdue() {
        return (!done && time(0) > deadline);
    }
    
    bool isDone() {
        return done;
    }
    
    friend void printTask(const Task& t);
};

void printTask(const Task& t) {
	
    cout << "\nTitle: " << t.title;
    cout << "\nDescription: " << t.description;
    cout << "\nStatus: " << (t.done ? "Done" : "Not Done");
    cout << "\nCreated: " << ctime(&t.createDate);
    cout << "Deadline: " <<ctime(&t.deadline);
    cout << "Priority: " << t.priority;
    if (!t.done && time(0) > t.deadline)
        cout << " Overdue.";
    cout << "\n-------------------\n";
}

class Todo : public Task {
	
public:
    Todo(string t, string d, time_t dl, string p)
        : Task(t, d, dl, p) {}
};

class TodoList {
	
private:
    vector<Todo> tasks;

public:
    void addTask(Todo t) {
        tasks.push_back(t);
    }

    void showAll() {
    	
        if (tasks.empty()) {
            cout << "\nNo tasks available.\n";
            cout << "\n-------------------\n";
            return;
        }
        for (int i = 0; i < tasks.size(); i++) {
            cout << "\nTask #" << i + 1;
            printTask(tasks[i]); 
        }
    }

    void showByStatus(bool status) {
    	
        bool found = false;
        for (int i = 0; i < tasks.size(); i++) {
            if (tasks[i].isDone()== status ) {
                printTask(tasks[i]);
                found = true;
            }
        }
        if (!found) {
             cout << "\nNo matching tasks.\n";
             cout << "\n-------------------\n";
            }
    }

    void showOverdue() {
    	
        bool found = false;
        for (int i = 0; i < tasks.size(); i++) {
            if (tasks[i].isOverdue()) {
                printTask(tasks[i]);
                found = true;
            }
        }
        if (!found) {
              cout << "\nNo overdue tasks.\n";
              cout << "\n-------------------\n";
            }
    }

    void toggleTask(int index) {
    	
        if (index >= 0 && index < tasks.size())
            tasks[index].toggleDone();
        else
            cout << "\nInvalid task number.\n";
            cout << "\n-------------------\n";
    }

    void removeTask(int index) {
    	
        if (index >= 0 && index < tasks.size())
            tasks.erase(tasks.begin() + index);
        else
            cout << "\nInvalid task number.\n";
            cout << "\n-------------------\n";
    }
};

int main() {
	
    TodoList myList;
    int choice;

    while (true) {
        cout << "-TODO LIST MENU-"<<endl;
        cout << "1. Add Task"<<endl;
        cout << "2. Show All Tasks"<<endl;
        cout << "3. Show Done Tasks"<<endl;
        cout << "4. Show Not Done Tasks"<<endl;
        cout << "5. Show Overdue Tasks"<<endl;
        cout << "6. Toggle Task Status"<<endl;
        cout << "7. Remove Task"<<endl;
        cout << "8. Exit"<<endl;
        cout << "______________________"<<endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string t, d, p;
            int year, month, day;

            cout << "Enter title: ";
            getline(cin, t);
            cout << "Enter description: ";
            getline(cin, d);
            cout << "Enter priority (Low / Medium / High): ";
            getline(cin, p);

            cout << "Enter deadline (Year Month Day): ";
            cin >> year >> month >> day;
            cin.ignore();

            tm temp = {};
            temp.tm_year = year - 1900;
            temp.tm_mon = month - 1;
            temp.tm_mday = day;
            time_t dl = mktime(&temp);

            Todo newTask(t, d,dl, p);
            
            myList.addTask(newTask);
            cout << "\nTask added successfully.\n"<<endl;
            cout << "-------------------"<<endl;
   }
   else if (choice == 2) {
            myList.showAll();
        }
		else if (choice == 3) {
            myList.showByStatus(true);
        }
		else if (choice == 4) {
            myList.showByStatus(false);
        }
		else if (choice == 5) {
            myList.showOverdue();
        }
		else if (choice == 6) {
            int num;
            cout << "Enter task number to toggle: ";
            cin >> num;
            cin.ignore();
            myList.toggleTask(num - 1);
        }
		else if (choice == 7) {
            int num;
            cout << "Enter task number to remove: ";
            cin >> num;
            cin.ignore();
            myList.removeTask(num - 1);
        }
		else if (choice == 8) {
            cout << "Exiting..."<<endl;
            break;
        }
		else {
            cout << "Invalid choice.Try again."<<endl;
            cout << "-------------------"<<endl;
        }
    }

    return 0;
}
