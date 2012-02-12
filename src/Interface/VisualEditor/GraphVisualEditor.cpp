/* 
    This file is part of Rocs.
    Copyright 2008-2011  Tomaz Canabrava <tomaz.canabrava@gmail.com>
    Copyright 2008       Ugo Sangiori <ugorox@gmail.com>
    Copyright 2011       Andreas Cord-Landwehr <cola@uni-paderborn.de>

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

#include "GraphVisualEditor.h"
#include "GraphScene.h"
#include "MainWindow.h"
#include "DataItem.h"
#include "PointerItem.h"

#include "Document.h"
#include "DataStructure.h"
#include "Data.h"
#include "Pointer.h"

#include "AlignAction.h"
#include "settings.h"

#include <QVBoxLayout>
#include <QGraphicsItem>
#include <KDebug>
#include <QGraphicsView>
#include <QPainter>
#include <DocumentManager.h>

GraphVisualEditor::GraphVisualEditor( MainWindow *parent) :
    QWidget(parent)
{
    _scene = 0;
    _document = 0;
    _mainWindow = parent;
    setupWidgets();
}

GraphVisualEditor* GraphVisualEditor::_self = 0;

GraphVisualEditor* GraphVisualEditor::self() {
    if (!_self){
        _self = new GraphVisualEditor();
    }
    return _self;
}

void GraphVisualEditor::resizeEvent (QResizeEvent  *event )
{
    Q_UNUSED(event);

    _scene->updateMinSize(size().width(), size().height());
}

void GraphVisualEditor::setupWidgets() {
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setContentsMargins(0,0,0,0);
    _scene = new GraphScene( this );
    _graphicsView = new QGraphicsView();
    _graphicsView->setRenderHints(QPainter::Antialiasing);
    _graphicsView->setOptimizationFlags(QGraphicsView::DontAdjustForAntialiasing);
    _graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    _graphicsView->setScene(_scene);
//     _graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    vLayout -> addWidget ( _graphicsView );
    setLayout( vLayout );
}

QGraphicsView* GraphVisualEditor::view() const {
    return _graphicsView;
}

void GraphVisualEditor::setActiveDocument( ) {
    if ( _document !=  DocumentManager::self()->activeDocument()) {
        releaseDocument();
    }
    _document = DocumentManager::self()->activeDocument();
    _scene->setActiveDocument();

    connect(_document , SIGNAL(activeDataStructureChanged(DataStructurePtr)),
            this ,       SLOT  (setActiveGraph(DataStructurePtr)));
}

void GraphVisualEditor::releaseDocument() {
    if (!_document){
        return;
    }

    _scene->clear();
    foreach(DataStructurePtr ds, _document->dataStructures()){
       ds->disconnect(this);
    }
}

//void GraphVisualEditor::drawGraphOnScene( DataStructure */*g*/) {}

void GraphVisualEditor::setActiveGraph( DataStructurePtr g) {
    _dataStructure = g;
    _scene->setActiveGraph(g);
}

GraphScene* GraphVisualEditor::scene() const {
    return _scene;
}

QList<DataItem*> GraphVisualEditor::selectedNodes() const {
    QList<DataItem*> tmpList;
    QList<QGraphicsItem*> l = _scene->selectedItems();
    foreach(QGraphicsItem *i, l) {
        if ( qgraphicsitem_cast<DataItem*>(i) ) {
            tmpList.append( qgraphicsitem_cast<DataItem*>(i) );
        }
    }
    return tmpList;
}