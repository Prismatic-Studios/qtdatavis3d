/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the QtDataVis3D module.
**
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
**
****************************************************************************/

#include "qbardataitem_p.h"

QT_DATAVIS3D_BEGIN_NAMESPACE

/*!
 * \class QBarDataItem
 * \inmodule QtDataVis3D
 * \brief The QBarDataItem class provides a container for resolved data to be added to bar graphs.
 * \since 1.0.0
 *
 * A QBarDataItem holds data for a single rendered bar in a graph.
 * Bar data proxies parse data into QBarDataItem instances for visualizing.
 *
 * \sa QBarDataProxy, {Qt Data Visualization 3D C++ Classes}
 */

/*!
 * Constructs QBarDataItem.
 */
QBarDataItem::QBarDataItem()
    : d_ptr(0), // private data doesn't exist by default (optimization)
      m_value(0.0)
{
}

QBarDataItem::QBarDataItem(qreal value)
    : d_ptr(0),
      m_value(value)
{
}

QBarDataItem::QBarDataItem(const QBarDataItem &other)
{
    operator=(other);
}

/*!
 * Destroys QBarDataItem.
 */
QBarDataItem::~QBarDataItem()
{
    delete d_ptr;
}

QBarDataItem &QBarDataItem::operator=(const QBarDataItem &other)
{
    m_value = other.m_value;
    if (other.d_ptr)
        createExtraData();
    else
        d_ptr = 0;
    // TODO set extra data
    return *this;
}

void QBarDataItem::setValue(qreal value)
{
    m_value = value;
}

qreal QBarDataItem::value() const
{
    return m_value;
}

void QBarDataItem::createExtraData()
{
    if (!d_ptr)
        d_ptr = new QBarDataItemPrivate;
}


QBarDataItemPrivate::QBarDataItemPrivate()
{
}

QBarDataItemPrivate::~QBarDataItemPrivate()
{
}

QT_DATAVIS3D_END_NAMESPACE