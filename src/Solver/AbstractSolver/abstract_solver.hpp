#ifndef ABSTRACT_SOLVER_HPP
#define ABSTRACT_SOLVER_HPP

#include <vector>
#include <map>

#include "../../Node/node.hpp"

using NodesMap = std::vector<std::vector<int>>;
using ForwardMap = std::map<int, std::vector<int>>;

class AbstractSolver {
public:
    virtual Times Solve(NodesMap &nodesmap, ForwardMap &forwardmap);
};

#endif