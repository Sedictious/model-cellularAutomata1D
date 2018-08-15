/**
 * Evoplex <https://evoplex.org>
 * Copyright (C) 2016-present
 */

#include "plugin.h"

namespace evoplex {

bool MinimalModel::init()
{
    // gets the id of the `state` node's attribute, which is the same for all nodes
    m_stateAttrId = node(0).attrs().indexOf("state");

    // initializing model attributes, which is constant throughout the simulation
    m_toroidal = attr("toroidal").toBool();
    // if the structure is toroidal, this attribute is irrelevant
    m_edgeCaseValue = attr("edgeCaseValue").toBool();
    // determines which rule to use
    m_rule = attr("rule").toInt();

    return m_stateAttrId >= 0;
}

bool MinimalModel::algorithmStep()
{
    std::vector<bool> nextStates;
    nextStates.reserve(nodes().size());

    for (Node node : nodes()) {
        bool left_cell, right_cell;
        if (node.id() == 0) { // Edge case 1: first cell
            if (m_toroidal) {
                left_cell = nodes().at(nodes().size()-1).attr(m_stateAttrId).toBool(); // the left cell is the last cell
            } else {
                left_cell = m_edgeCaseValue; // the left cell is the edge case value
            }

            right_cell = nodes().at(1).attr(m_stateAttrId).toBool();
        } else if (node.id() == (nodes().size()-1)) { // Edge case 2: last cell
            if (m_toroidal) {
                right_cell = nodes().at(0).attr(m_stateAttrId).toBool(); // the right cell is the first cell
            } else {
                right_cell = m_edgeCaseValue; // the right cell is the edge case value
            }

            left_cell = nodes().at(nodes().size()-2).attr(m_stateAttrId).toBool();
        } else {
            // For all other cells
            left_cell = nodes().at(node.id()-1).attr(m_stateAttrId).toBool();
            right_cell = nodes().at(node.id()+1).attr(m_stateAttrId).toBool();
        }

        bool central_cell = node.attr(m_stateAttrId).toBool();

        bool central_cell_next_state;

        switch (m_rule) {
        case 30:
            central_cell_next_state = left_cell ^ (central_cell || right_cell);
            break;
        case 110:
            central_cell_next_state = (right_cell && !central_cell) || (!left_cell && central_cell) || (!right_cell && central_cell);
            break;
        default:
            break;
        }

        nextStates.emplace_back(central_cell_next_state);
    }

    size_t i = 0;
    for (Node node : nodes()) {
        node.setAttr(m_stateAttrId, Value(nextStates.at(i)).toBool());
        ++i;
    }
    return true;
}

} // evoplex
REGISTER_PLUGIN(MinimalModel)
#include "plugin.moc"
