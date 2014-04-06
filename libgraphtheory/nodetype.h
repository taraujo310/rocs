/*
 *  Copyright 2014  Andreas Cord-Landwehr <cordlandwehr@kde.org>
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) version 3, or any
 *  later version accepted by the membership of KDE e.V. (or its
 *  successor approved by the membership of KDE e.V.), which shall
 *  act as a proxy defined in Section 6 of version 3 of the license.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef NODETYPE_H
#define NODETYPE_H

#include "libgraphtheoryexport.h"
#include "typenames.h"

#include <QObject>
#include <QSharedPointer>

namespace GraphTheory
{

class NodeTypePrivate;

/**
 * \class Node
 */
class GRAPHTHEORY_EXPORT NodeType : public QObject
{
    Q_OBJECT

public:
    /**
     * Creates a new node type and registers it at @p document.
     *
     * @param document  the GraphDocument containing this node type
     * @return a NodeType object
     */
    static NodeTypePtr create(GraphDocumentPtr document);

    /** Destroys the edge type */
    virtual ~NodeType();

    /**
     * Destroys the node type object and removes it from the document.
     */
    void destroy();

    /**
     * The valid state returns @c true if the object is created and can be used, @c false if it is
     * not yet created or about to be removed
     *
     * @return the validity state of the object
     */
    bool isValid() const;

    /**
     * Debug method that tracks how many node objects exist.
     *
     * @return number of node type objects
     */
    static uint objects()
    {
        return objectCounter;
    }

protected:
    NodeType();

private:
    Q_DISABLE_COPY(NodeType)
    const QScopedPointer<NodeTypePrivate> d;
    void setQpointer(NodeTypePtr q);
    static uint objectCounter;
};
}

#endif
