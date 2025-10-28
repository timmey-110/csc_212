#include "tracer.h"
#include "scheduler.h"
#include "task.h"
#include <iostream>
#include <random>
#include <vector>

int main() {
    constexpr int NUM_TASKS = 10000;
    constexpr int MAX_ARRIVAL = 5000;
    constexpr int MAX_DURATION = 50;
    constexpr int MAX_PRIORITY = 100;

    std::mt19937 rng(42);
    std::uniform_int_distribution<int> arrival_dist(0, MAX_ARRIVAL);
    std::uniform_int_distribution<int> duration_dist(1, MAX_DURATION);
    std::uniform_int_distribution<int> priority_dist(1, MAX_PRIORITY);

    std::vector<Task> tasks;
    tasks.reserve(NUM_TASKS);
    for (int i = 0; i < NUM_TASKS; ++i) {
        int tick = arrival_dist(rng);
        int duration = duration_dist(rng);
        int priority = priority_dist(rng);
        tasks.emplace_back(tick, duration, priority);
    }

    Tracer tracer(std::move(tasks));
    Scheduler scheduler;

    int total_cost = tracer.trace(scheduler);

    std::cout << "Number of tasks: " << NUM_TASKS << "\n";
    std::cout << "Total weighted delay: " << total_cost << "\n";
    std::cout << "Average weighted delay per task: " << static_cast<double>(total_cost) / NUM_TASKS << "\n";

    return 0;
}
