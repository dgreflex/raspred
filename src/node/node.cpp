#include <memory>

#include "node.hpp"

Node::Node() : message_buffer(""), rank(0) {}
Node::Node(const std::string &start_message) : message_buffer(start_message), rank(0) {}
Node::Node(const std::string &start_message, const int rank) : message_buffer(start_message), rank(rank) {}
Node::Node(const int rank) : rank(rank) {}

NodePtr Node::GetPtr() const {
    return std::make_shared<Node>(*this);
}

std::size_t Node::GetMessageSize() const {
    return this->message_buffer.size();
}

void Node::SetRank(const int rank) {
    this->rank = rank;
}

int Node::GetRank() const {
    return this->rank;
}

