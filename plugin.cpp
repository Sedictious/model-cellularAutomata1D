/**
 * Evoplex <https://evoplex.org>
 * Copyright (C) 2016-present
 */

#include "plugin.h"

namespace evoplex {

bool MinimalModel::init()
{
    m_stateAttrId = node(0).attrs().indexOf("state");
    return m_stateAttrId >= 0;
}

bool MinimalModel::algorithmStep()
{
    std::vector<bool> nextStates;
    nextStates.reserve(nodes().size());

    for (Node node : nodes()) {
        if(node.id() == 0 || node.id() == (nodes().size()-1)){ // Edge cases
            continue;
        } else {
//            left_cell XOR (central_cell OR right_cell)
//            bool left_cell = nodes.at(node.id()-1).attr(m_stateAttrId).toBool();
        }
    }
    return true;
}

} // evoplex
REGISTER_PLUGIN(MinimalModel)
#include "plugin.moc"
