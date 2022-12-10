#ifndef ABSTRACT_SPLITTER_HPP
#define ABSTRACT_SPLITTER_HPP

#include <cstdint>
#include <utility>

class AbstractSplitter {
public:
    virtual std::pair<std::uint64_t, std::uint64_t> Split(std::uint64_t message_size);
};

#endif