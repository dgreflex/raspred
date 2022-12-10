#include "random_splitter.hpp"

#include <cstdint>
#include <utility>

RandomSplitter::RandomSplitter() : rd(), mt(rd()), dist(0.0, 1.0) {}
RandomSplitter::RandomSplitter(const std::string& token) : rd(token), mt(rd()), dist(0.0, 1.0) {}

const double RandomSplitter::GetRandomValue() {
    return this->dist(this->mt);
}

std::pair<std::uint64_t, std::uint64_t> RandomSplitter::Split(std::uint64_t message_size) {
    std::uint64_t first = message_size * this->GetRandomValue();
    return std::make_pair(first, message_size - first);
}