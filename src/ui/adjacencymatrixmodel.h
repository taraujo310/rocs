/*
 *  Copyright 2012-2014  Thiago Ururay <tufa.araujo@kde.org>
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License as
 *  published by the Free Software Foundation; either version 2 of
 *  the License or (at your option) version 3 or any later version
 *  accepted by the membership of KDE e.V. (or its successor approved
 *  by the membership of KDE e.V.), which shall act as a proxy
 *  defined in Section 14 of version 3 of the license.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ADJACENCYMATRIXMODEL_H
#define ADJACENCYMATRIXMODEL_H

#include "libgraphtheory/graphdocument.h"
#include "libgraphtheory/adjacencymatrix.h"
#include <QAbstractTableModel>
#include <QString>

using namespace GraphTheory;

class AdjacencyMatrixModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    AdjacencyMatrixModel(QObject *parent = nullptr);

    void setGraph(GraphTheory::GraphDocumentPtr graph);
    void disconnectGraph();
    void connectGraph();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    void setWeightPropertyName(QString weightProperty);

private:
    void generateMatrix();
    void onGraphChanged();
    void onPropertyChange(int index);
    void onEdgeAdded();

private:
    GraphTheory::GraphDocumentPtr m_graph = nullptr;
    GraphTheory::AdjacencyMatrix *m_matrix = nullptr;
    QString m_weightPropertyName = nullptr;
};

#endif
