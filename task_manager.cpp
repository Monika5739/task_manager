#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct Task {
    int id;
    string description;
};

class TaskManager {
private:
    vector<Task> tasks;
    const string fileName = "tasks.txt";

    // Function to load tasks from the file
    void loadTasks() {
        ifstream file(fileName);
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            Task task;
            ss >> task.id;
            getline(ss, task.description);
            tasks.push_back(task);
        }
        file.close();
    }

    // Function to save tasks to the file
    void saveTasks() {
        ofstream file(fileName, ios::trunc);
        for (const auto& task : tasks) {
            file << task.id << " " << task.description << endl;
        }
        file.close();
    }

public:
    TaskManager() {
        loadTasks();
    }

    // Function to display tasks
    void displayTasks() {
        if (tasks.empty()) {
            cout << "No tasks available." << endl;
            return;
        }

        cout << "Task ID | Description" << endl;
        cout << "----------------------" << endl;
        for (const auto& task : tasks) {
            cout << task.id << " | " << task.description << endl;
        }
    }

    // Function to add a task
    void addTask() {
        string description;
        cout << "Enter task description: ";
        cin.ignore(); // to ignore any leftover newline character in the input buffer
        getline(cin, description);
        
        int id = tasks.empty() ? 1 : tasks.back().id + 1;
        Task newTask = {id, description};
        tasks.push_back(newTask);
        saveTasks();
        cout << "Task added successfully." << endl;
    }

    // Function to remove a task
    void removeTask() {
        int taskId;
        cout << "Enter task ID to remove: ";
        cin >> taskId;
        
        bool found = false;
        for (auto it = tasks.begin(); it != tasks.end(); ++it) {
            if (it->id == taskId) {
                tasks.erase(it);
                saveTasks();
                found = true;
                cout << "Task removed successfully." << endl;
                break;
            }
        }

        if (!found) {
            cout << "Task ID not found." << endl;
        }
    }
};

int main() {
    TaskManager manager;
    int choice;

    do {
        cout << "\nTask Manager Menu" << endl;
        cout << "1. Add Task" << endl;
        cout << "2. Remove Task" << endl;
        cout << "3. Display Tasks" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                manager.addTask();
                break;
            case 2:
                manager.removeTask();
                break;
            case 3:
                manager.displayTasks();
                break;
            case 4:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
