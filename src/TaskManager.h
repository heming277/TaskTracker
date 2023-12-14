//taskmanager.h
#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include "Task.h"
#include "DatabaseInterface.h"

class TaskManager {
public:
    TaskManager(DatabaseInterface& dbInterface);
    void addTask(const Task& task);
    void removeTask(int taskId);
    void updateTaskStatus(int taskId, const std::string& newStatus);
    std::vector<Task> getAllTasks();

private:
    DatabaseInterface& db;
};

#endif // TASKMANAGER_H