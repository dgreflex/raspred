#ifndef NODE_HPP
#define NODE_HPP

#include <string>
#include <memory>

class Node;

using NodePtr = std::shared_ptr<Node>;

class Node {
private:
    std::string message_buffer;
    int rank;

public:
    explicit Node();
    explicit Node(const std::string &start_message);
    explicit Node(const std::string &start_message, const int rank);
    explicit Node(const int rank);
    ~Node() = default;
    int Send(NodePtr recipient, const std::size_t message_size);
    int Recv(NodePtr sender, const std::size_t message_size);
    NodePtr GetPtr() const;
    std::size_t GetMessageSize() const;
    void SetRank(const int rank);
    int GetRank() const;
};

#endif