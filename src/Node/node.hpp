#ifndef NODE_HPP
#define NODE_HPP

#include <mpi.h>
#include <vector>
#include <cstdint>

#include "../Splitter/AbstractSplitter/abstract_splitter.hpp"

using Times = std::vector<std::uint64_t>;

class Node {
private:
    std::uint64_t message_size;
    Times total_time;
    int core_rank;
    int in_quantity;
    int out_quantity;
    AbstractSplitter splitter;

    void RSync(const int rank);
    void SSync(const int rank);

public:
    explicit Node();
    explicit Node(AbstractSplitter &splitter, const int core_rank, const int in_quantity, const int out_quantity);
    explicit Node(AbstractSplitter &splitter, const int core_rank, const int in_quantity, const int out_quantity, const std::uint64_t &message_size);
    MPI_Status Run();
    void Collect() const;
};

#endif