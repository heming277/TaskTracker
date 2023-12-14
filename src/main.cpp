//main.cpp
#include "TaskManager.h"
#include "DatabaseInterface.h"
#include <iostream>
#include <limits>
#include <string>
#include <cstdlib>
#include <map>

int main() {

    const char* dbHost = std::getenv("DB_HOST");
    const char* dbUser = std::getenv("DB_USER");
    const char* dbPassword = std::getenv("DB_PASSWORD");
    const char* dbPort = std::getenv("DB_PORT");
    const char* dbName = std::getenv("DB_NAME");

    // Check if the environment variables are set
    std::string host = dbHost ? dbHost : "localhost";
    std::string user = dbUser ? dbUser : "default_user";
    std::string password = dbPassword ? dbPassword : "default_password";
    std::string port = dbPort ? dbPort : "5432";
    std::string name = dbName ? dbName : "task_tracker_db";

    // Construct the connection string
    std::string connectionString = "postgresql://" + user + ":" + password + "@" + host + ":" + port + "/" + name;

    DatabaseInterface dbInterface(connectionString);
    TaskManager taskManager(dbInterface);

    std::string command;
    std::map<int, int> displayIdToInternalIdMap;

    while (true) {
        std::cout << "Enter command (add, remove, update, list, quit): ";
        std::cin >> command;

        if (command == "add") {
            std::string description;
            std::cout << "Enter task description: ";
            std::cin >> std::ws; // Skip any leading whitespace.
            std::getline(std::cin, description);
            Task newTask(0, description, "To Begin"); //waiting to begin
            taskManager.addTask(newTask);
        } else if (command == "remove") {
            int displayId;
            std::cout << "Enter task ID to remove: ";
            std::cin >> displayId;
            if (displayIdToInternalIdMap.count(displayId) > 0) {
                int internalId = displayIdToInternalIdMap[displayId];
                taskManager.removeTask(internalId);
            } else {
                std::cout << "Invalid task ID.\n";
            }
        } else if (command == "update") {
            int displayId;
            std::string newStatus;
            std::cout << "Enter task ID and new status: ";
            std::cin >> displayId;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the remaining characters on the current line.
            std::getline(std::cin, newStatus); // Use getline to read the entire status including spaces.
            if (displayIdToInternalIdMap.count(displayId) > 0) {
                int internalId = displayIdToInternalIdMap[displayId];
                taskManager.updateTaskStatus(internalId, newStatus);
            } else {
                std::cout << "Invalid task ID.\n";
            }
        } else if (command == "list") {
            std::cout << "Current tasks:\n";
            std::vector<Task> tasks = taskManager.getAllTasks();
            displayIdToInternalIdMap.clear(); // Clear the old mapping
            int displayId = 1;
            for (const Task& task : tasks) {
                std::cout << "Task ID: " << displayId << ", Description: " << task.getDescription()
                          << ", Status: " << task.getStatus() << '\n';
                displayIdToInternalIdMap[displayId] = task.getId();
                displayId++;
            }
        } else if (command == "quit") {
            break;
        } else {
            std::cout << "Unknown command. Please try again.\n";
        }
    }

    return 0;
}