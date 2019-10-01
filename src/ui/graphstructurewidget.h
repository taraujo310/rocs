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

#ifndef GRAPHSTRUCTUREWIDGET_H
#define GRAPHSTRUCTUREWIDGET_H

#include <QWidget>
#include <QTableView>
#include "project/project.h"
#include "adjacencymatrixmodel.h"
#include <QLineEdit>

class GraphStructureWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GraphStructureWidget(QWidget* parent);
    void setProject(Project *project);

private:
    void mountLayout();

private Q_SLOTS:
    void onGraphDocumentChange(GraphTheory::GraphDocumentPtr document);
    void setWeightProperty();

private:
    Project *m_project; //!< current project
    QTableView *m_graphStructureTable;
    AdjacencyMatrixModel *m_adjacencyMatrixModel;
    QLineEdit *m_weightProperty = nullptr;
};

#endif
