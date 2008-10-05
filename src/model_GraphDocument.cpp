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
#include "model_GraphDocument.h"
#include "libgraph_GraphDocument.h"
#include "libgraph_Graph.h"
#include <QString>
#include <QDebug>
#include <QModelIndex>

GraphDocumentModel::GraphDocumentModel(QList<libgraph::GraphDocument*>* documents, QObject *parent)
  : QAbstractListModel( parent ), _documents( (*documents) ){
}

int GraphDocumentModel::rowCount(const QModelIndex &parent) const{
  return _documents.size();
}

QVariant GraphDocumentModel::data(const QModelIndex &index, int role) const{
  if ( !index.isValid() ) return QVariant();
  if ( index.row() > _documents.size()) return QVariant();
  if ( role != Qt::DisplayRole) return QVariant();

  return _documents.at(index.row())->name();
}

QVariant GraphDocumentModel::headerData(int section, Qt::Orientation orientation, int role) const{
  if ( role != Qt::DisplayRole) return QVariant();
  if (orientation == Qt::Horizontal) return QString("Column %1").arg(section);
  else return QString("Row %1").arg(section);
}

Qt::ItemFlags GraphDocumentModel::flags(const QModelIndex& index) const{
  if ( !index.isValid() ) return Qt::ItemIsEnabled;
  return QAbstractItemModel::flags(index); // | Qt::ItemIsEditable;
}

bool GraphDocumentModel::setData(const QModelIndex& index, const QVariant& value, int role){
  if ( index.isValid() && (role == Qt::ItemIsEditable)) {
    _documents.at(index.row())-> setName(value.toString());
    emit dataChanged(index, index);
    return true;
  }
  return false;
}

bool GraphDocumentModel::insertRows(int position, int rows, const QModelIndex &index){
  beginInsertRows(QModelIndex(), position, position+rows-1);  
  
  libgraph::GraphDocument *doc = new libgraph::GraphDocument("untitled");
  _documents.append(doc);
  
  endInsertRows();
  return true;
}

bool GraphDocumentModel::removeRows(int position, int rows, const QModelIndex &index){
     beginRemoveRows(QModelIndex(), position, position+rows-1);
    _documents.removeAt(position);
     endRemoveRows();
     return true;
}

libgraph::GraphDocument *GraphDocumentModel::at(const QModelIndex& index)
{
  return _documents.at(index.row());
}