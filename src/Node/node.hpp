#ifndef NODE_HPP
#define NODE_HPP

#include <mpi.h>
#include <vector>
#include <cstdint>

#include "../Splitter/ProportionalSplitter/proportional_splitter.hpp"

using Times = std::vector<std::uint64_t>;

class Node {
private:
    std::uint64_t message_size;
    Times total_time;
    int core_rank;
    int in_quantity;
    int out_quantity;
    ProportionalSplitter splitter;

    void RSync(const int rank);
    void SSync(const int rank);

public:
    explicit Node();
    explicit Node(ProportionalSplitter &splitter, const int core_rank, const int in_quantity, const int out_quantity);
    explicit Node(ProportionalSplitter &splitter, const int core_rank, const int in_quantity, const int out_quantity, const std::uint64_t &message_size);
    MPI_Status Run();
    void Collect() const;
};

#endif