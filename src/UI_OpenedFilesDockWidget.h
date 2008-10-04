
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

#ifndef UI_OPENED_FILES_DOCK_WIDGET_H
#define UI_OPENED_FILES_DOCK_WIDGET_H

#include "ui_OpenedFilesDockWidget.h"
#include <QDockWidget>

class GraphDocumentModel;

namespace libgraph{
  class GraphDocument;
}

/*! 
  \brief The Graph-Layer widget.
  This Holds in a layer-way (like Photoshop Layers) the Graphs of the current opened Graph File 
*/
class OpenedFilesDockWidget : public QDockWidget, public Ui::OpenedFilesDockWidget{
  Q_OBJECT

  public:
    OpenedFilesDockWidget(GraphDocumentModel *model, QWidget* parent = 0, Qt::WindowFlags flags = 0);
  
  signals:
    void activeDocumentChanged(libgraph::GraphDocument *document);

  private slots:
    void changeActiveDocument(const QModelIndex& model);
    void on__btnNewFile_clicked();

  private:
    GraphDocumentModel *_documentModel;
};

#endif
