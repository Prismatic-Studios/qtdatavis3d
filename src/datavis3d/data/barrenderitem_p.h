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

//
//  W A R N I N G
//  -------------
//
// This file is not part of the QtDataVis3D API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef BARRENDERITEM_P_H
#define BARRENDERITEM_P_H

#include "abstractrenderitem_p.h"

QT_DATAVIS3D_BEGIN_NAMESPACE

class Bars3dRenderer;

class BarRenderItem : public AbstractRenderItem
{
public:
    BarRenderItem();
    virtual ~BarRenderItem();

    // Position relative to data window (for bar label generation)
    inline void setPosition(const QPoint &pos) { m_position = pos; }
    inline const QPoint &position() const { return m_position; }

    // Actual cached data value of the bar (needed to trigger label reformats)
    inline void setValue(qreal value);
    inline qreal value() const { return m_value; }

    // Normalized bar height
    inline void setHeight(GLfloat height) { m_height = height; }
    inline GLfloat height() const { return m_height; }

    // TODO should be in abstract, but currently there is no abstract renderer
    inline void setRenderer(Bars3dRenderer *renderer) { m_renderer = renderer; }

protected:
    virtual void formatLabel();

    Bars3dRenderer *m_renderer;
    qreal m_value;
    QPoint m_position; // x = row, y = column
    GLfloat m_height;

    friend class QBarDataItem;
};

void BarRenderItem::setValue(qreal value)
{
    if (m_value != value) {
        m_value = value;
        if (!m_label.isNull())
            setLabel(QString()); // Forces reformatting on next access
    }
}

typedef QVector<BarRenderItem> BarRenderItemRow;
typedef QVector<BarRenderItemRow> BarRenderItemArray;

QT_DATAVIS3D_END_NAMESPACE

#endif