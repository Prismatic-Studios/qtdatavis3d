/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Data Visualization module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

//
//  W A R N I N G
//  -------------
//
// This file is not part of the QtDataVisualization API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef QSURFACE3DSERIES_P_H
#define QSURFACE3DSERIES_P_H

#include "qsurface3dseries.h"
#include "qabstract3dseries_p.h"

QT_BEGIN_NAMESPACE

class QSurface3DSeriesPrivate : public QAbstract3DSeriesPrivate
{
    Q_OBJECT
public:
    QSurface3DSeriesPrivate(QSurface3DSeries *q);
    virtual ~QSurface3DSeriesPrivate();

    void setDataProxy(QAbstractDataProxy *proxy) override;
    void connectControllerAndProxy(Abstract3DController *newController) override;
    void createItemLabel() override;

    void setSelectedPoint(const QPoint &position);
    void setFlatShadingEnabled(bool enabled);
    void setDrawMode(QSurface3DSeries::DrawFlags mode);
    void setTexture(const QImage &texture);
    void setWireframeColor(const QColor &color);

private:
    QSurface3DSeries *qptr();

    QPoint m_selectedPoint;
    bool m_flatShadingEnabled;
    QSurface3DSeries::DrawFlags m_drawMode;
    QImage m_texture;
    QString m_textureFile;
    QColor m_wireframeColor;

private:
    friend class QSurface3DSeries;
};

QT_END_NAMESPACE

#endif
