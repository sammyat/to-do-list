#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <Windows.h>

struct Task {
    std::string description;
    bool completed;

    Task(const std::string& desc) : description(desc), completed(false) {}
};

void printTasks(const std::vector<Task>& tasks) {
    std::cout << "Tasks:\n";
    for (size_t i = 0; i < tasks.size(); ++i) {
        std::cout << "[" << (tasks[i].completed ? "x" : " ") << "] " << i + 1 << ". " << tasks[i].description << "\n";
    }
}

void addTask(std::vector<Task>& tasks, const std::string& description) {
    tasks.emplace_back(description);
    std::cout << "Task added: " << description << "\n";

    // Save tasks to file
    std::ofstream file("tasks.txt");
    if (file.is_open()) {
        for (const Task& task : tasks) {
            file << task.description << "," << task.completed << "\n";
        }
        file.close();
    }
    else {
        std::cout << "Unable to save tasks to file.\n";
    }
}

void completeTask(std::vector<Task>& tasks, int index) {
    if (index >= 0 && index < tasks.size()) {
        tasks[index].completed = true;
        std::cout << "Task completed: " << tasks[index].description << "\n";

        // Save tasks to file
        std::ofstream file("tasks.txt");
        if (file.is_open()) {
            for (const Task& task : tasks) {
                file << task.description << "," << task.completed << "\n";
            }
            file.close();
        }
        else {
            std::cout << "Unable to save tasks to file.\n";
        }
    }
    else {
        std::cout << "Invalid task index!\n";
    }
}

void printHelp() {
    std::cout << "Commands:\n";
    std::cout << "  help         - Display available commands\n";
    std::cout << "  list         - Display the task list\n";
    std::cout << "  add <task>   - Add a new task\n";
    std::cout << "  complete <n> - Mark task number <n> as completed\n";
    std::cout << "  exit         - Quit the program\n";
}

int main() {
    std::vector<Task> tasks;

    SetConsoleTitleA("To-do List");

    std::cout << "To-Do List Application\n";
    std::cout << "Enter 'help' for a list of commands.\n";

    // Load tasks from file
    std::ifstream file("tasks.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            size_t commaPos = line.find(",");
            if (commaPos != std::string::npos) {
                Task task(line.substr(0, commaPos));
                task.completed = (line.substr(commaPos + 1) == "1");
                tasks.push_back(task);
            }
        }
        file.close();
    }
    else {
        std::cout << "No tasks file found. Creating a new one.\n";
    }

    while (true) {
        std::string userInput;
        std::cout << "> ";
        std::getline(std::cin, userInput);

        if (userInput == "exit") {
            break;
        }
        else if (userInput == "list") {
            printTasks(tasks);
        }
        else if (userInput.substr(0, 4) == "add ") {
            std::string description = userInput.substr(4);
            addTask(tasks, description);
        }
        else if (userInput.substr(0, 8) == "complete ") {
            int index = std::stoi(userInput.substr(8));
            completeTask(tasks, index - 1);
        }
        else if (userInput == "help") {
            printHelp();
        }
        else {
            std::cout << "Invalid command! Enter 'help' for a list of commands.\n";
        }
    }

    return 0;
}
