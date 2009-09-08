#ifndef SUI_NODEPROPERTIESWIDGET_H
#define SUI_NODEPROPERTIESWIDGET_H

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
#include <QWidget>
#include "ui_NodePropertiesWidget.h"
 
class GraphPropertiesModel;
class QGraphicsItem;
class Graph;
class Node;
class Edge;
class MainWindow;

/*! \brief Properties Area, not used yet. */
class NodePropertiesWidget : public QWidget, public Ui::NodePropertiesWidget
{
    Q_OBJECT
public:
    NodePropertiesWidget (MainWindow* parent = 0 );
    void setNode(Node *n);
    
private slots:
  void on__name_textChanged(const QString& s);
  void on__value_textChanged(const QString& s);
  void on__x_valueChanged(int i);
  void on__y_valueChanged(int i);
  void on__size_valueChanged(int i);
  
private:

    Node *_node;
    MainWindow *_mainWindow;
    
};
#endif
