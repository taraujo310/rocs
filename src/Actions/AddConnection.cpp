/* This file is part of Rocs,
   Copyright (C) 2008 by:
   Tomaz Canabrava <tomaz.canabrava@gmail.com>
   Ugo Sangiori <ugorox@gmail.com>

   Rocs is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   Rocs is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Step; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "AddConnection.h"
#include "GraphScene.h"
#include "DataStructure.h"
#include "Data.h"
#include "Pointer.h"
#include "DataItem.h"
#include "PointerItem.h"
#include <KLocale>

#include <KDebug>
#include <DocumentManager.h>
#include <Document.h>

AddConnectionAction::AddConnectionAction(GraphScene *scene, QObject *parent)
        : AbstractAction(scene, parent) {
    setText(i18n ( "Add Edge" ));
    setToolTip ( i18n ( "Creates a new edge between 2 nodes" ) );
    setIcon ( KIcon ( "rocsaddedge" ) );

    _from = 0;
    _to   = 0;
    _tmpLine  = 0;
    _working = false;
    _name = "add-edge";
}

AddConnectionAction::~AddConnectionAction() {
    kDebug() << "Destroyed";
}

void AddConnectionAction::executePress(QPointF pos) {
    if (_working) return;
    if ( !  DocumentManager::self()->activeDocument()->activeDataStructure() 
         || DocumentManager::self()->activeDocument()->activeDataStructure()->readOnly())
     return;
    
    _working = true;
    _from = qgraphicsitem_cast<DataItem*>(_graphScene->itemAt(pos));

    if ( ! _from ) {
        _working = false;
        return;
    }
    _startPos = QPointF(_from->datum()->x(), _from->datum()->y());
}

void AddConnectionAction::executeMove(QPointF pos) {
    if ( !DocumentManager::self()->activeDocument()->activeDataStructure() ) return;
    if ( !_from ) return;

    if ( !_tmpLine ) {
        _tmpLine = new QGraphicsLineItem();
        _graphScene->addItem(_tmpLine);
    }

    _tmpLine->setLine(_startPos.x(), _startPos.y(), pos.x(), pos.y());
}

void AddConnectionAction::executeRelease(QPointF pos) {
    if ( !_working ) return;
    if ( !DocumentManager::self()->activeDocument()->activeDataStructure() ) return;

    if ( _tmpLine ) {
        delete _tmpLine;
        _tmpLine = 0;
    }

    _to = qgraphicsitem_cast<DataItem*>(_graphScene->itemAt(pos));
    if (  _to ) {
        DocumentManager::self()->activeDocument()->activeDataStructure()->addPointer( _from->datum(),  _to->datum() );
    }

    _to = 0;
    _from = 0;
    _working = false;
}