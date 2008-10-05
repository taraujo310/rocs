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

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <KXmlGuiWindow>
#include <QList>
#include <QStringList>

/* WORKING */
class PaletteBarDockWidget;
class OpenedFilesDockWidget;
class GraphLayersDockWidget;
class GraphEditWidget;
class GraphDocumentModel;
class GraphLayersModel;

namespace libgraph{
  class GraphDocument;
}

class MainWindow : public KXmlGuiWindow{
Q_OBJECT

public:
  /*! defalt constructor */
  MainWindow();
  
private:
  PaletteBarDockWidget*  _PaletteBar;   // area where the icons of actions will be.
  OpenedFilesDockWidget* _OpenedFiles;  // area where the opened files will be
  GraphLayersDockWidget* _GraphLayers;  // area where the layers of the active graph will appear.
  GraphEditWidget* _GraphEdit; // Area where the graph will be editted.

  void setupModels();  // setup all the models to be used on the views.
  void setupWidgets(); // Setup all the widgets
  void setupActions(); // Setup all the actions.

  QList<libgraph::GraphDocument*> _documents;
  GraphDocumentModel *_documentModel;
  GraphLayersModel   *_graphLayersModel;
};

#endif