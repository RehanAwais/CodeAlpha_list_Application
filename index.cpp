#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

// Task class
class Task {
public:
    string title;
    string category;
    bool completed;

    Task(string t, string c, bool comp = false) {
        title = t;
        category = c;
        completed = comp;
    }
};

// Function declarations
void addTask(vector<Task> &tasks);
void viewTasks(const vector<Task> &tasks, bool showCompleted);
void markTaskCompleted(vector<Task> &tasks);
void saveTasks(const vector<Task> &tasks);
void loadTasks(vector<Task> &tasks);

int main() {
    vector<Task> tasks;
    int choice;

    loadTasks(tasks);

    do {
        cout << "\n===== TASK MANAGER =====\n";
        cout << "1. Add Task\n";
        cout << "2. View Pending Tasks\n";
        cout << "3. View Completed Tasks\n";
        cout << "4. Mark Task as Completed\n";
        cout << "5. Save & Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                addTask(tasks);
                break;
            case 2:
                viewTasks(tasks, false);
                break;
            case 3:
                viewTasks(tasks, true);
                break;
            case 4:
                markTaskCompleted(tasks);
                break;
            case 5:
                saveTasks(tasks);
                cout << "Tasks saved. Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}

// Add new task
void addTask(vector<Task> &tasks) {
    string title, category;

    cout << "Enter task title: ";
    getline(cin, title);

    cout << "Enter category (optional): ";
    getline(cin, category);

    tasks.push_back(Task(title, category));
    cout << "Task added successfully!\n";
}

// View tasks
void viewTasks(const vector<Task> &tasks, bool showCompleted) {
    cout << "\n===== TASK LIST =====\n";
    bool found = false;

    for (int i = 0; i < tasks.size(); i++) {
        if (tasks[i].completed == showCompleted) {
            cout << i + 1 << ". " << tasks[i].title;

            if (!tasks[i].category.empty())
                cout << " [" << tasks[i].category << "]";

            cout << endl;
            found = true;
        }
    }

    if (!found)
        cout << "No tasks found.\n";
}

// Mark task as completed
void markTaskCompleted(vector<Task> &tasks) {
    int index;
    viewTasks(tasks, false);

    cout << "Enter task number to mark as completed: ";
    cin >> index;

    if (index > 0 && index <= tasks.size() && !tasks[index - 1].completed) {
        tasks[index - 1].completed = true;
        cout << "Task marked as completed!\n";
    } else {
        cout << "Invalid task number!\n";
    }
}

// Save tasks to file
void saveTasks(const vector<Task> &tasks) {
    ofstream file("tasks.txt");

    for (int i = 0; i < tasks.size(); i++) {
        file << tasks[i].title << "|"
             << tasks[i].category << "|"
             << tasks[i].completed << endl;
    }

    file.close();
}

// Load tasks from file
void loadTasks(vector<Task> &tasks) {
    ifstream file("tasks.txt");
    if (!file)
        return;

    string title, category;
    bool completed;

    while (getline(file, title, '|')) {
        getline(file, category, '|');
        file >> completed;
        file.ignore();

        tasks.push_back(Task(title, category, completed));
    }

    file.close();
}

