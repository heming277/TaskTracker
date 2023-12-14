//task.cpp
#include "Task.h"

Task::Task(int id, std::string description, std::string status)
    : id(id), description(std::move(description)), status(std::move(status)) {
}

int Task::getId() const {
    return id;
}

std::string Task::getDescription() const {
    return description;
}

std::string Task::getStatus() const {
    return status;
}

void Task::setDescription(const std::string& newDescription) {
    description = newDescription;
}

void Task::setStatus(const std::string& newStatus) {
    status = newStatus;
}