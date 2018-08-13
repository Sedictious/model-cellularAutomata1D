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

    return false;
}

} // evoplex
REGISTER_PLUGIN(MinimalModel)
#include "plugin.moc"
