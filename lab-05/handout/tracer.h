#pragma once
#include <vector>
#include "scheduler.h"
#include "task.h"

class Tracer {
    std::vector<Task> m_tasks;

public:
    explicit Tracer(std::vector<Task>&& tasks);

    int trace(Scheduler& scheduler) const;
};