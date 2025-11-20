#pragma once
#include <string>
#include <vector>
#include <cstdint>

struct Component {
    std::string name;

    explicit Component(std::string &&name) : name(name) {
    }
};

struct Device {
    std::vector<Component> components;
    std::vector<std::pair<Component, Component> > connections;

    Device(std::vector<Component> &&components,
           std::vector<std::pair<Component, Component> > &&connections) : components(components),
                                                                          connections(connections) {
    }
};

[[nodiscard]] std::uint32_t strategic_silicon(const Device &device, std::size_t height, std::size_t width);

