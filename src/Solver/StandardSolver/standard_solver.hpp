#ifndef STANDARD_SOLVER_HPP
#define STANDARD_SOLVER_HPP

#include "../../Node/node.hpp"

using ForwardMap = std::map<int, std::vector<int>>;

class StandardSolver {
private:
    void ReccursiveNodeRunner(ForwardMap &forwardmap) const;

public:
    Times Solve(ForwardMap &forwardmap) const;
    static StandardSolver &getInstance();
};

#endif