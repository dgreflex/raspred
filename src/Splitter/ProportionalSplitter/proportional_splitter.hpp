#ifndef PROPORTIONAL_SPLITTER_HPP
#define PROPORTIONAL_SPLITTER_HPP

#include <cstdint>
#include <utility>

class ProportionalSplitter {
private:
    double proportion;

public:
    explicit ProportionalSplitter();
    explicit ProportionalSplitter(const double proportion);
    virtual std::pair<std::uint64_t, std::uint64_t> Split(std::uint64_t message_size);
};

#endif