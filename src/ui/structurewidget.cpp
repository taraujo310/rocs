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
#include "project/project.h"
#include <QGridLayout>
#include <QLabel>
#include <QTableView>
#include <QList>
#include <QString>

StructureWidget::StructureWidget(QWidget* parent)
    : QWidget(parent)
    , m_project(Q_NULLPTR)
{
    m_graphModel = new GraphModel(this);
    m_graphStructureTable = new QTableView(this);
}

void StructureWidget::setProject(Project *project)
{
    if (m_project) {
        m_project->disconnect(this);
    }

    m_project = project;

    connect(project, static_cast<void (Project::*)(GraphTheory::GraphDocumentPtr)>(&Project::activeGraphDocumentChanged),
        this, &StructureWidget::onGraphDocumentChange);


    this->mountLayout();
}

void StructureWidget::onGraphDocumentChange(GraphTheory::GraphDocumentPtr document)
{
    GraphTheory::GraphDocumentPtr graph = document;
    m_graphModel->setGraph(graph);
}

void StructureWidget::mountLayout()
{
    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(new QLabel("Matriz de Adjacência"));

    GraphTheory::GraphDocumentPtr graph = m_project->activeGraphDocument();

    m_graphModel->setGraph(graph);

    m_graphStructureTable->setModel(m_graphModel);
    layout->addWidget(m_graphStructureTable);

    layout->addWidget(new QLabel("Matriz de Incidência"));
}
