//task.h
#ifndef TASK_H
#define TASK_H

#include <string>

class Task {
public:
    Task(int id, std::string description, std::string status);

    // Getters
    int getId() const;
    std::string getDescription() const;
    std::string getStatus() const;

    // Setters 
    void setDescription(const std::string& newDescription);
    void setStatus(const std::string& newStatus);

private:
    int id;
    std::string description;
    std::string status;
};

#endif // TASK_H