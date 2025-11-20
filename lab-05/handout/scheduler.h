#pragma once
#include <cstddef>
#include "task.h"

class Scheduler {
    // TODO: Add member variables.

public:
    Scheduler();

    // TODO: Add a task to the list of pending tasks.
    void push(Task task);

    // TODO: Return the next pending task to execute. The task should be removed from the scheduler state. If the task
    // does not finish execution, `push` will be called with the updated task.
    [[nodiscard]] Task pop_next();

    // TODO: Return the number of pending tasks.
    [[nodiscard]] size_t size() const;
};