#pragma once
#include <vector>
#include <cassert>
#include <cstdint>

enum class Base {
    Adenine, Cytosine, Guanine, Thymine
};

class DNA {
    std::vector<Base> m_bases;

public:
    explicit DNA(std::vector<Base> bases) : m_bases(std::move(bases)) {
    }

    [[nodiscard]] const Base &operator[](const std::size_t index) const noexcept {
        assert(index < size());
        return m_bases[index];
    }

    [[nodiscard]] std::size_t size() const noexcept { return m_bases.size(); }
};

[[nodiscard]] std::uint32_t genetic_gap(const DNA &dna1, const DNA &dna2);
