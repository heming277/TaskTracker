
// DatabaseInterface.h
#ifndef DATABASEINTERFACE_H
#define DATABASEINTERFACE_H

#include <pqxx/pqxx>
#include "Task.h"

class DatabaseInterface {
public:
    DatabaseInterface(const std::string& connection_str);
    void saveTask(const Task& task);
    void deleteTask(int taskId);
    void updateTaskStatus(int taskId, const std::string& newStatus); 
    std::vector<Task> getAllTasks();
    

private:
    pqxx::connection dbConnection;
};

#endif // DATABASEINTERFACE_H