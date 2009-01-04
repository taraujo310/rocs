/***************************************************************************
 * main.cpp
 * This file is part of the KDE project
 * copyright (C)2004-2007 by Tomaz Canabrava (tomaz.canabrava@gmail.com)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 * You should have received a copy of the GNU Library General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 ***************************************************************************/

#ifndef NODE_H
#define NODE_H

#ifndef USING_QTSCRIPT 
#define USING_QTSCRIPT 1
#endif

#include <QObject>
#include <QList>
#include <QVariant>

#ifdef USING_QTSCRIPT
#include <QtScript>
#include "qtScriptBackend.h"
#endif

class Edge;

class Node : public QObject{
Q_OBJECT

public:
  Node(QObject *parent);
  ~Node();
  void addInEdge(Edge *e);
  void addOutEdge(Edge *e);
  void addSelfEdge(Edge *e);
  void removeEdge(Edge *e, int edgeList);
  void removeEdge(Edge *e, QList<Edge*> *list);
  enum EdgeLists{In, Out, Self};

#ifdef USING_QTSCRIPT
	QScriptValue scriptValue() const;
	void setEngine(	QtScriptBackend *_engine );
	QScriptValue createScriptArray(QList<Edge*> list);
#endif

public  slots:
  QList<Node*> adjacent_nodes() const;
  QList<Edge*> adjacent_edges() const;
  QList<Edge*> edges(Node *n);
  QList<Edge*> in_edges() const;
  QList<Edge*> out_edges() const;
  QList<Edge*> self_edges() const;

#ifdef USING_QTSCRIPT
	QScriptValue adj_nodes();
	QScriptValue adj_edges();
	QScriptValue input_edges();
	QScriptValue output_edges();
	QScriptValue loop_edges();
	QScriptValue connected_edges(Node *n);
#endif

  Edge* addEdge(Node* to);

private:
  QList<Edge*> _in_edges;
  QList<Edge*> _out_edges;
  QList<Edge*> _self_edges;
  void empty(QList<Edge*> *list);

#ifdef USING_QTSCRIPT
	QScriptValue _value;
	QtScriptBackend *_engine;
#endif

signals:
  void removed();
};

#endif