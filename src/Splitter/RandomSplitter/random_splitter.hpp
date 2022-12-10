#ifndef RANDOM_SPLITTER_HPP
#define RANDOM_SPLITTER_HPP

#include <cstdint>
#include <utility>
#include <random>

#include "../AbstractSplitter/abstract_splitter.hpp"

class RandomSplitter : public AbstractSplitter {
private:
    std::random_device rd;
    std::mt19937 mt;
    std::uniform_int_distribution<double> dist;

    const double GetRandomValue();

public:
    explicit RandomSplitter();
    explicit RandomSplitter(const std::string &token);
    virtual std::pair<std::uint64_t, std::uint64_t> Split(std::uint64_t message_size) override;
};

#endif