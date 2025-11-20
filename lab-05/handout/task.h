#pragma once

class Task {
    int m_duration;
    int m_priority;
    int m_tick;

public:
    Task(int duration, int priority, int tick) : m_duration(duration), m_priority(priority), m_tick(tick) { }

    int duration() const { return m_duration; }
    int priority() const { return m_priority; }

    friend class Tracer;
};