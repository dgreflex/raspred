#include <iostream>
#include <mpi.h>
#include <vector>
#include <map>
#include <algorithm>
#include <cstdlib>

#include "src/Node/node.hpp"
#include "src/Solver/StandardSolver/standard_solver.hpp"
#include "src/Splitter/ProportionalSplitter/proportional_splitter.hpp"

/* matrix = {
    {1,  3,  6,  10, 15},
    {2,  5,  9,  14, 19},
    {4,  8,  13, 18, 22},
    {7,  12, 17, 21, 24},
    {11, 16, 20, 23, 25},
}
*/
ForwardMap forward = {
    {1,  {2, 3}},
    {2,  {4, 5}},
    {3,  {5, 6}},
    {4,  {7, 8}},
    {5,  {8 ,9}},
    {6,  {9, 10}},
    {7,  {11, 12}},
    {8,  {12, 13}},
    {9,  {13, 14}},
    {10, {14, 15}},
    {11, {16}},
    {12, {16, 17}},
    {13, {17, 18}},
    {14, {18, 19}},
    {15, {19}},
    {16, {20}},
    {17, {20, 21}},
    {18, {21, 22}},
    {19, {22}},
    {20, {23}},
    {21, {23, 24}},
    {22, {24}},
    {23, {25}},
    {24, {25}},
};

int main(int argc, char *argv[]) {
    int numprocs, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::uint64_t start_message = 1000;
    if (argc > 1)
        start_message = std::atoll(argv[1]);

    if (rank) {
        ProportionalSplitter my_splitter = ProportionalSplitter(0.5);
        Node my_node;
        switch (rank) {
            case 1:
                my_node = Node(my_splitter, 0, 0, 2, 1000);
                break;
            case 25:
                my_node = Node(my_splitter, 0, 2, 0);
                break;
            case 2:
            case 3:
            case 4:
            case 6:
            case 7:
            case 10:
                my_node = Node(my_splitter, 0, 1, 2);
                break;
            case 11:
            case 15:
                my_node = Node(my_splitter, 0, 1, 1);
                break;
            case 16:
            case 19:
            case 20:
            case 22:
            case 23:
            case 24:
                my_node = Node(my_splitter, 0, 2, 1);
                break;
            default:
                my_node = Node(my_splitter, 0, 2, 2);
                break;
            }

            MPI_Status status = my_node.Run();
            if (status.MPI_ERROR != MPI_SUCCESS)
                std::cerr << "Error in: " << rank << " | " << status.MPI_ERROR << std::endl;
            if (rank == 25)
                my_node.Collect();
    } else {
        StandardSolver solver = StandardSolver::getInstance();
        auto result = solver.Solve(forward);
        std::uint64_t max = *std::max_element(result.begin(), result.end());
        std::cout << "Result: " << max << std::endl;
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}