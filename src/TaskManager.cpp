//taskmanager.cpp
#include "TaskManager.h"

TaskManager::TaskManager(DatabaseInterface& dbInterface) : db(dbInterface) {}

void TaskManager::addTask(const Task& task) {
    db.saveTask(task);
}

void TaskManager::removeTask(int taskId) {
    db.deleteTask(taskId);
}

void TaskManager::updateTaskStatus(int taskId, const std::string& newStatus) {
    db.updateTaskStatus(taskId, newStatus);
}

std::vector<Task> TaskManager::getAllTasks() {
    return db.getAllTasks();
}