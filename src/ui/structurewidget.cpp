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

#include "structurewidget.h"
#include "graphmodel.h"
#include <QGridLayout>
#include <QLabel>
#include <QTableView>
#include <QList>
#include <QString>

StructureWidget::StructureWidget(QWidget* parent)
    : QWidget(parent)
{
    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(new QLabel("Matriz de Adjacência"));

    QList<QString> edges;
    QList<QString> nodes;

    edges.append("1");
    edges.append("2");
    edges.append("3");
    edges.append("4");

    nodes.append("a");
    nodes.append("b");
    nodes.append("c");
    nodes.append("d");

    GraphModel *graph = new GraphModel();
    graph->setGraph(edges, nodes);

    QTableView *GraphStructure = new QTableView;
    GraphStructure->setModel(graph);
    layout->addWidget(GraphStructure);

    layout->addWidget(new QLabel("Matriz de Incidência"));
}
