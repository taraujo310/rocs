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
	 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
	 GNU General Public License for more details.

	 You should have received a copy of the GNU General Public License
	 along with Step; if not, write to the Free Software
	 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA	02110-1301	USA
*/


#include "NodeItem.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QPen>
#include <QBrush>
#include <QThread>

#include "node.h"
#include "graph.h"
#include "EdgeItem.h"
#include "OrientedEdgeItem.h"
#include <KDebug>
#include <QDebug>
#include <GraphScene.h>
#include <QTimeLine>

NodeItem::NodeItem(Node *node, QGraphicsItem *parent)
        : QObject(0), QGraphicsItem(parent)
{
    _node = node;
    _opacity = 0;
    connect(_node, SIGNAL(posChanged()), this, SLOT(updatePos()));
    QPointF pos( _node -> x() ,_node->y() );
    setPos( pos );
    setZValue(1);
    setFlag(ItemIsSelectable);
    connect (_node, SIGNAL(removed()), this, SLOT(remove()));
     QTimeLine *timeLine = new QTimeLine(500, this);
     timeLine->setFrameRange(0, 50);
     connect(timeLine, SIGNAL(frameChanged(int)), this, SLOT(removeOpacity()));
     timeLine->start();
     
   }

NodeItem::~NodeItem(){
//      QTimeLine *timeLine = new QTimeLine(500, this);
//      timeLine->setFrameRange(0, 50);
//      connect(timeLine, SIGNAL(frameChanged(int)), this, SLOT(addOpacity()));
//      timeLine->start();
//      sleep(500);
}
void NodeItem::removeOpacity(){
  if ( _opacity  < 1.0 ) _opacity += 0.1;
  if ( _opacity  > 1.0 ) _opacity = 1.0;
  update();
}

void NodeItem::addOpacity(){
  if ( _opacity > 0.0 ) _opacity -= 0.1;
  if ( _opacity < 0.0 ) _opacity = 0.0;
  update();
}

QRectF NodeItem::boundingRect() const {
     if ( _node->begin() ){
         return QRectF(-52, -12 , 65, 25);
     }
     if ( _removingBeginFlag ){
         return QRectF(-52, -12 , 65, 25);
     }
    return QRectF(-12, -12 , 25, 25);
}

QPainterPath NodeItem::shape() const {
    QPainterPath path;
    path.addEllipse(-10, -10, 20, 20);
    return path;
}

void NodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) {
    if (isSelected()) {
        QPen pen(Qt::black, 1, Qt::DotLine);

        painter->setBrush(QBrush());
        painter->setPen(pen);
        painter->drawRect(QRectF(-11 , -11 , 24 , 24 ));
    }
    if( _node->begin() ){
      if (_removingBeginFlag == false) _removingBeginFlag = true;
      painter->drawLine(-20, -10, 0, 0);
      painter->drawLine(-52, 0, 0, 0);
      painter->drawLine(-20, 10, 0, 0);
    }
    else if (_removingBeginFlag) _removingBeginFlag = false;

    painter->setPen(Qt::NoPen);
    QColor color = QColor(_node->color());
    color.setAlphaF(_opacity);
    painter->setBrush( color.dark(240) );

    painter->drawEllipse(-7, -7, 20, 20);
    QRadialGradient gradient(-3, -3, 10);
    
    if (option->state & QStyle::State_Sunken) {
        gradient.setColorAt(0, color.light(240));
        gradient.setColorAt(1, color);
    } else {
        gradient.setColorAt(0, color.light(240));
        gradient.setColorAt(1, color);
    }

    painter->setBrush(gradient);
    painter->setPen(QPen(color, 2));
    painter->drawEllipse(-10, -10, 20, 20);
    if( _node->end() ){
      QColor c(Qt::black);
      c.setAlphaF(_opacity);
      painter->setPen(c);
      painter->drawEllipse(-7, -7, 15, 15); 
    }
}

void NodeItem::updatePos() {  setPos( QPointF(_node->x(), _node->y() ) ); }
void NodeItem::updateName(const QString& ) {}
void NodeItem::updateVisited(bool ) {}
void NodeItem::updateValue(qreal ) {}
void NodeItem::updateTotal(qreal ) {}
void NodeItem::updateColor(QColor ) {}

void NodeItem::remove() {
  if (scene() == 0) return;
  dynamic_cast<GraphScene*>(scene())->removeGItem(this);
  deleteLater();
}

#include "NodeItem.moc"