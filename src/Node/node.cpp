#include <memory>
#include <mpi.h>
#include <cstdint>

#include "node.hpp"

Node::Node() : 
    message_size(0),
    total_time({}),
    core_rank(0),
    in_quantity(0),
    out_quantity(0) {}

Node::Node(ProportionalSplitter &splitter, const int core_rank, const int in_quantity, const int out_quantity) : Node() {
    this->core_rank = core_rank;
    this->in_quantity = in_quantity;
    this->out_quantity = out_quantity;
    this->splitter = splitter;
}

Node::Node(ProportionalSplitter &splitter, const int core_rank, const int in_quantity, const int out_quantity, const std::uint64_t &message_size) :
    Node(splitter, core_rank, in_quantity, out_quantity) {
    this->message_size = message_size;
}

void Node::RSync(const int rank) {
    char sync = 'a';
    MPI_Recv(&sync, 1, MPI_CHAR, rank, 0, MPI_COMM_WORLD, nullptr);
}

void Node::SSync(const int rank) {
    char sync = 'a';
    MPI_Send(&sync, 1, MPI_CHAR, rank, 0, MPI_COMM_WORLD);
}

MPI_Status Node::Run() {
    MPI_Status status_error = MPI_Status();
    char sync = 'a';

    if (in_quantity == 0)
        this->total_time.push_back(0);

    for (int i = 0; i < this->in_quantity; ++i) {
        int in_rank;
        MPI_Recv(&in_rank, 1, MPI_INT, this->core_rank, 0, MPI_COMM_WORLD, &status_error);
        if (status_error.MPI_ERROR != MPI_SUCCESS)
            return status_error;

        std::uint64_t message_and_times_size[2];
        this->RSync(in_rank);
        MPI_Recv(message_and_times_size, 2, MPI_UINT64_T, in_rank, 0, MPI_COMM_WORLD, &status_error);
        if (status_error.MPI_ERROR != MPI_SUCCESS)
            return status_error;

        this->message_size += message_and_times_size[0];
        std::uint64_t times[message_and_times_size[1]];
        this->RSync(in_rank);
        MPI_Recv(times, message_and_times_size[1], MPI_UINT64_T, in_rank, 0, MPI_COMM_WORLD, &status_error);
        if (status_error.MPI_ERROR != MPI_SUCCESS)
            return status_error;

        for (int j = 0; j < message_and_times_size[1]; ++j)
            this->total_time.push_back(times[j]);
    }

    auto splitted_sizes = this->splitter.Split(this->message_size);

    for (int i = 0; i < this->out_quantity; ++i) {
        int out_rank;
        MPI_Recv(&out_rank, 1, MPI_INT, this->core_rank, 0, MPI_COMM_WORLD, &status_error);
        if (status_error.MPI_ERROR != MPI_SUCCESS)
            return status_error;

        std::uint64_t message_and_times_size[2];
        if (!i)
            message_and_times_size[0] = splitted_sizes.first;
        else
            message_and_times_size[0] = splitted_sizes.second;
        message_and_times_size[1] = this->total_time.size();

        this->SSync(out_rank);
        MPI_Rsend(message_and_times_size, 2, MPI_UINT64_T, out_rank, 0, MPI_COMM_WORLD);
        std::uint64_t times[this->total_time.size()];
        for (int j = 0; j < this->total_time.size(); ++j)
            times[j] = this->total_time[j] + message_and_times_size[0];
        
        this->SSync(out_rank);
        MPI_Rsend(times, this->total_time.size(), MPI_UINT64_T, out_rank, 0, MPI_COMM_WORLD);
    }
    return status_error;
}

void Node::Collect() const {
    std::uint64_t size = this->total_time.size();
    MPI_Send(&size, 1, MPI_UINT64_T, this->core_rank, 0, MPI_COMM_WORLD);

    std::uint64_t times[this->total_time.size()];
    for (int i = 0; i < this->total_time.size(); ++i)
        times[i] = this->total_time[i];

    MPI_Send(times, this->total_time.size(), MPI_UINT64_T, this->core_rank, 0, MPI_COMM_WORLD);
}