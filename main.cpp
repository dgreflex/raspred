#include <iostream>
#include <mpi.h>
#include <vector>
#include <map>

#include "src/Node/node.hpp"
#include "src/Solution/"

const NodesMap matrix = {
    {1, 3, 6, 10, 15},
    {2, 5, 9, 14, 19},
    {4, 8, 13, 18, 22},
    {7, 12, 17, 21, 24},
    {11, 16, 20, 23, 25},
};
const ForwardMap forward = {
    1 : {2, 3},
};

int main(int argc, char *argv[]) {
    int numprocs, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    std::cout << numprocs << ":" << rank << std::endl;
    

    MPI_Finalize();
    return 0;
}