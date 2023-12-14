
//DatabaseInterface.cpp
#include "DatabaseInterface.h"

DatabaseInterface::DatabaseInterface(const std::string& connection_str) : dbConnection(connection_str) {}

void DatabaseInterface::saveTask(const Task& task) {
    pqxx::work W{dbConnection};
    W.exec0("INSERT INTO tasks (description, status) VALUES (" +
            W.quote(task.getDescription()) + ", " +
            W.quote(task.getStatus()) + ")");
    W.commit();
}

void DatabaseInterface::deleteTask(int taskId) {
    pqxx::work W{dbConnection};
    W.exec0("DELETE FROM tasks WHERE task_id = " + W.quote(taskId));
    W.commit();
}

void DatabaseInterface::updateTaskStatus(int taskId, const std::string& newStatus) {
    pqxx::work W{dbConnection};
    W.exec0("UPDATE tasks SET status = " + W.quote(newStatus) + " WHERE task_id = " + W.quote(taskId));
    W.commit();
}

std::vector<Task> DatabaseInterface::getAllTasks() {
    pqxx::work W{dbConnection};
    pqxx::result R = W.exec("SELECT task_id, description, status FROM tasks ORDER BY task_id ASC");

    std::vector<Task> tasks;
    for (auto row : R) {
        tasks.emplace_back(row[0].as<int>(), row[1].as<std::string>(), row[2].as<std::string>());
    }

    return tasks;
}