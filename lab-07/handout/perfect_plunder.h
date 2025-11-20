#pragma once
#include <cstdint>
#include <memory>

class House {
    std::uint32_t m_dollars;
    std::shared_ptr<House> m_left;
    std::shared_ptr<House> m_right;

public:
    explicit House(const uint32_t dollars) : m_dollars(dollars), m_left(nullptr), m_right(nullptr) {
    }

    [[nodiscard]] uint32_t dollars() const noexcept { return m_dollars; }

    [[nodiscard]] std::shared_ptr<House> &left() noexcept { return m_left; }

    [[nodiscard]] const std::shared_ptr<House> &left() const noexcept { return m_left; }

    [[nodiscard]] std::shared_ptr<House> &right() noexcept { return m_right; }

    [[nodiscard]] const std::shared_ptr<House> &right() const noexcept { return m_right; }
};

[[nodiscard]] uint32_t perfect_plunder(const std::shared_ptr<House> &cul_de_sac);
