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

#ifndef ADJACENCYMATRIX_H
#define ADJACENCYMATRIX_H

#include "typenames.h"
#include "node.h"
#include "edge.h"
#include "graphdocument.h"

namespace GraphTheory
{

class GRAPHTHEORY_EXPORT AdjacencyMatrix
{

public:
    AdjacencyMatrix(GraphTheory::GraphDocumentPtr graph = nullptr);
    void calculate();
    void print();
    int getValue(int i, int j);
    int getEdgeWeight(EdgePtr edge);
    void setValue(int i, int j, int value);
    void setWeightPropertyName(const QString &propertyName);
    int size();

private:
    GraphTheory::GraphDocumentPtr m_graph = nullptr;
    std::vector<int> m_matrix;
    QString m_weightPropertyName;
    int lastSize;

};
}

#endif
