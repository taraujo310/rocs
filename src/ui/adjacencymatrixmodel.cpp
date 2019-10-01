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

#include "adjacencymatrixmodel.h"
#include "libgraphtheory/adjacencymatrix.h"
#include "libgraphtheory/graphdocument.h"
#include <QtGlobal>
#include <iostream>

using namespace GraphTheory;

AdjacencyMatrixModel::AdjacencyMatrixModel(QObject *parent) : QAbstractTableModel(parent)
{
}

void AdjacencyMatrixModel::setGraph(GraphTheory::GraphDocumentPtr graph)
{
    beginResetModel();

    if (m_graph) {
        m_graph->disconnect(this);

        for (int i = 0; i < m_graph->edges().size(); i++) {
            EdgePtr edge = m_graph->edges().at(i);
            edge->disconnect(this);
        }
    }

    m_graph = graph;
    this->generateMatrix();


    connect(m_graph.data(), QOverload<>::of(&GraphTheory::GraphDocument::nodeAdded),
        this, &AdjacencyMatrixModel::onGraphChanged);
    connect(m_graph.data(), QOverload<>::of(&GraphTheory::GraphDocument::nodesRemoved),
        this, &AdjacencyMatrixModel::onGraphChanged);
    connect(m_graph.data(), QOverload<>::of(&GraphTheory::GraphDocument::edgeAdded),
        this, &AdjacencyMatrixModel::onEdgeAdded);
    connect(m_graph.data(), QOverload<>::of(&GraphTheory::GraphDocument::edgesRemoved),
        this, &AdjacencyMatrixModel::onGraphChanged);

    for (int i = 0; i < m_graph->edges().size(); i++) {
        EdgePtr edge = m_graph->edges().at(i);

        connect(edge.get(), QOverload<int>::of(&GraphTheory::Edge::dynamicPropertyChanged),
            this, &AdjacencyMatrixModel::onPropertyChange, Qt::UniqueConnection);
    }

    endResetModel();

    return;
}

int AdjacencyMatrixModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_graph->nodes().size();
}

int AdjacencyMatrixModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_graph->nodes().size();
}


QVariant AdjacencyMatrixModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) {
        return {};
    }

    return m_matrix->getValue(index.row(), index.column());
}

QVariant AdjacencyMatrixModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(orientation);
    if (role == Qt::DisplayRole) {
        return m_graph->nodes().at(section)->id();
    }
    return QVariant();
}

void AdjacencyMatrixModel::generateMatrix()
{
    if (m_matrix) {
        m_matrix->destroy();
    }

    m_matrix = new AdjacencyMatrix(m_graph);
    m_matrix->create();
    m_matrix->calculate();
}

void AdjacencyMatrixModel::onGraphChanged()
{
    this->setGraph(m_graph);
    return;
}

void AdjacencyMatrixModel::onEdgeAdded() {
    EdgePtr edge = m_graph->edges().last();

    int row = m_graph->nodes().indexOf(edge->from());
    int column = m_graph->nodes().indexOf(edge->to());
    int weight = edge->dynamicProperty(m_weightPropertyName).toInt();
    weight = weight != 0 ? weight : 1;

    m_matrix->setValue(row, column, weight);

    connect(edge.get(), QOverload<int>::of(&GraphTheory::Edge::dynamicPropertyChanged),
        this, &AdjacencyMatrixModel::onPropertyChange, Qt::UniqueConnection);

    if (edge->type()->direction() == EdgeType::Direction::Bidirectional) {
        m_matrix->setValue(column, row, weight);
        emit this->dataChanged(this->index(0, 0), this->index(m_graph->nodes().size() - 1, m_graph->nodes().size() - 1));
    } else {
        emit this->dataChanged(this->index(row, column), this->index(row, column));
    }

}

void AdjacencyMatrixModel::onPropertyChange(int index) {
    Q_UNUSED(index);
    Edge* edge = qobject_cast<Edge*>(sender());

    int row = m_graph->nodes().indexOf(edge->from());
    int column = m_graph->nodes().indexOf(edge->to());
    int weight = edge->dynamicProperty(m_weightPropertyName).toInt();
    weight = weight ? weight : 1;

    m_matrix->setValue(row, column, weight);

    if (edge->type()->direction() == EdgeType::Direction::Bidirectional) {
        m_matrix->setValue(column, row, weight);
    }
}

void AdjacencyMatrixModel::setWeightPropertyName(QString propertyName)
{
    m_weightPropertyName = propertyName;
    m_matrix->setWeightPropertyName(m_weightPropertyName);
    emit this->dataChanged(this->index(0, 0), this->index(m_graph->nodes().size() - 1, m_graph->nodes().size() - 1));
}
