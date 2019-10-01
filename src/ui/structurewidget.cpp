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
#include <QtGlobal>
#include <QLineEdit>

#include <KLocalizedString>

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

    connect(project, QOverload<GraphTheory::GraphDocumentPtr>::of(&Project::activeGraphDocumentChanged),
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
    layout->addWidget(new QLabel(i18nc("@title:group", "Adjacency Matrix")), 0, 0, 1, 2);

    if (m_weightProperty) {
        m_weightProperty->disconnect(this);
    }

    m_weightProperty = new QLineEdit;

    layout->addWidget(new QLabel(i18nc("@label:textbox", "Weight%1", ": ")), 1, 0);
    layout->addWidget(m_weightProperty, 1, 1);

    connect(m_weightProperty, QOverload<>::of(&QLineEdit::editingFinished),
        this, &StructureWidget::setWeightProperty);

    GraphTheory::GraphDocumentPtr graph = m_project->activeGraphDocument();

    m_graphModel->setGraph(graph);

    m_graphStructureTable->setModel(m_graphModel);
    layout->addWidget(m_graphStructureTable, 2, 0, 1, 2);
}

void StructureWidget::setWeightProperty()
{
    m_graphModel->setWeightPropertyName(m_weightProperty->text());
}
