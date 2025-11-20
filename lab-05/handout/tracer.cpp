#include "tracer.h"
#include <algorithm>

Tracer::Tracer(std::vector<Task> &&tasks) : m_tasks(std::move(tasks)) {
    std::sort(m_tasks.begin(), m_tasks.end(), [](const Task& a, const Task& b) { return a.m_tick < b.m_tick; });
}


int Tracer::trace(Scheduler &scheduler) const {
    int cost = 0;
    int tick = 0;
    int idx = 0;
    while (idx < m_tasks.size() || scheduler.size() > 0) {
        while (idx < m_tasks.size() && m_tasks[idx].m_tick <= tick) {
            scheduler.push(m_tasks[idx]);
            ++idx;
        }

        if (scheduler.size() > 0) {
            auto task = scheduler.pop_next();
            task.m_duration -= 1;
            if (task.m_duration != 0)
                scheduler.push(task);
            else
                cost += task.m_priority * (tick - task.m_tick + 1);
        }

        ++tick;
    }
    return cost;
}
