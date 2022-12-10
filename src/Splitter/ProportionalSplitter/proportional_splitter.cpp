#include "proportional_splitter.hpp"

ProportionalSplitter::ProportionalSplitter() : proportion(0.5) {}
ProportionalSplitter::ProportionalSplitter(const double proportion) : proportion(proportion) {}

std::pair<std::uint64_t, std::uint64_t> ProportionalSplitter::Split(std::uint64_t message_size) {
    std::uint64_t first = message_size * this->proportion;
    return std::make_pair(first, message_size - first);
}