#include <mpi.h>
#include <cstdint>
#include <iostream>

#include "standard_solver.hpp"

void StandardSolver::ReccursiveNodeRunner(ForwardMap &forwardmap) const {
    for (int i = 1; i < forwardmap.size() + 1; ++i)
        if (forwardmap.find(i) != forwardmap.end()) {
            for (int &next_node : forwardmap[i]) {
                MPI_Send(&i, 1, MPI_INT, next_node, 0, MPI_COMM_WORLD);
                MPI_Send(&next_node, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            }
        }
}

Times StandardSolver::Solve(ForwardMap &forwardmap) const {
    this->ReccursiveNodeRunner(forwardmap);
    std::uint64_t size;
    MPI_Recv(&size, 1, MPI_UINT64_T, 25, 0, MPI_COMM_WORLD, nullptr);
    Times result;
    result.reserve(size);
    std::uint64_t times[size];
    MPI_Recv(times, size, MPI_UINT64_T, 25, 0, MPI_COMM_WORLD, nullptr);
    for (int i = 0; i < size; ++i)
        result.push_back(times[i]);
    return result;
}

StandardSolver &StandardSolver::getInstance() {
    static StandardSolver instance;
    return instance;
}