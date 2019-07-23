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

#include "graphmodel.h"

GraphModel::GraphModel(QObject *parent) : QAbstractTableModel(parent)
{
}

void GraphModel::setGraph(const QList<QString> &edges, const QList<QString> &nodes)
{
    m_edges.clear();
    m_edges = edges;
    m_nodes.clear();
    m_nodes = nodes;
    return;
}

int GraphModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_edges.length();
}

int GraphModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_nodes.length();
}


QVariant GraphModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) {
        return 1;
    }
    if (index.column() == 0) {
        return 1;
    } else if (index.column() == 1) {
        return 1;
    }
    return 1;
}

QVariant GraphModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            return m_edges[section];
        } else {
            return m_nodes[section];
        }
    }
    return QVariant();
}
