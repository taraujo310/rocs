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
#include "graphmodel.h"
#include "libgraphtheory/edge.h"
#include "libgraphtheory/graphdocument.h"

using namespace GraphTheory;

GraphModel::GraphModel(QObject *parent) : QAbstractTableModel(parent)
{
}

void GraphModel::setGraph(GraphTheory::GraphDocumentPtr graph)
{
    beginResetModel();

    m_graph = graph;

    if (m_matrix) {
        delete[] m_matrix;
    }

    m_matrix = this->createMatrix();
    this->calculateAdjancencyMatrix();

    endResetModel();

    return;
}

int GraphModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_graph->nodes().size();
}

int GraphModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_graph->nodes().size();
}


QVariant GraphModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) {
        return {};
    }

    return m_matrix[m_graph->nodes().size() * index.row() + index.column()];
}

QVariant GraphModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        return m_graph->nodes().at(section)->id();
    }
    return QVariant();
}

int* GraphModel::createMatrix() {
    int size = m_graph->nodes().size();
    int *matrix = new int[size * size];

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[size * i + j] = 0;
        }
    }

    return matrix;
}

void GraphModel::calculateAdjancencyMatrix()
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

void GraphModel::printMatrix()
{
    int size = m_graph->nodes().size();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << m_matrix[size * i + j] << " ";
        }
        std::cout << "\n";
    }
}
