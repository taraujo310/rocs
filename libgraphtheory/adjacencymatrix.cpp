/*
    This file is part of Rocs.
    Copyright 2019       Thiago Ururay <tufa.araujo@kde.org>

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation; either version 2 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include "typenames.h"
#include "node.h"
#include "edge.h"
#include "graphdocument.h"
#include "adjacencymatrix.h"

using namespace GraphTheory;

AdjacencyMatrix::AdjacencyMatrix(GraphTheory::GraphDocumentPtr graph) : QObject()
{
    m_graph = graph;
}

int* AdjacencyMatrix::create() {
    int size = m_graph->nodes().size();
    int *matrix = new int[size * size];

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[size * i + j] = 0;
        }
    }

    return matrix;
}

void AdjacencyMatrix::calculate()
{
    int size = m_graph->nodes().size();

    for (int i = 0; i < size; i++) {
        NodePtr rowNode = m_graph->nodes().at(i);

        for (int j = 0; j < rowNode->edges().size(); j++) {
            EdgePtr edge = rowNode->edges().at(j);

            NodePtr fromNode = edge.get()->to();
            NodePtr toNode = edge.get()->from();

            if (fromNode->id() == toNode->id()) { // edge is a Loop
                m_matrix[size * i + i] = 1;
            } else {
                NodePtr columnNode = (rowNode->id() == fromNode->id()) ? toNode : fromNode;
                int index = m_graph->nodes().indexOf(columnNode);

                m_matrix[size * i + index] = 1;
            }
        }
    }

    return;
}

void AdjacencyMatrix::print()
{
    int size = m_graph->nodes().size();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << m_matrix[size * i + j] << " ";
        }
        std::cout << "\n";
    }
}

int AdjacencyMatrix::getValue(int i, int j)
{
    return m_matrix[m_graph->nodes().size() * i + j];
}
