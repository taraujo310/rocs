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

#include "nodetype.h"
#include "graphdocument.h"

using namespace GraphTheory;

// initialize number of node type objects
uint NodeType::objectCounter = 0;

class GraphTheory::NodeTypePrivate {
public:
    NodeTypePrivate()
        : m_valid(false)
    {
    }

    ~NodeTypePrivate()
    {
    }

    NodeTypePtr q;
    GraphDocumentPtr m_document;
    bool m_valid;
};

NodeType::NodeType()
    : QObject()
    , d(new NodeTypePrivate)
{
    ++NodeType::objectCounter;
}

NodeType::~NodeType()
{
    --NodeType::objectCounter;
}

NodeTypePtr NodeType::create(GraphDocumentPtr document)
{
    NodeTypePtr pi(new NodeType);
    pi->setQpointer(pi);
    pi->d->m_document = document;
    pi->d->m_valid = true;

    // insert completely initialized node type into document
    document->insert(pi->d->q);
    return pi;
}

void NodeType::destroy()
{
    d->m_valid = false;
    d->m_document->remove(d->q);

    // reset last reference to this object
    d->q.reset();
}

bool NodeType::isValid() const
{
    return d->m_valid;
}

void NodeType::setQpointer(NodeTypePtr q)
{
    d->q = q;
}
