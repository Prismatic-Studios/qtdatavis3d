/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtDataVis3D module.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "maprenderitem_p.h"
#include "maps3drenderer_p.h" // TODO remove when maps refactored
#include "maps3dcontroller_p.h" // TODO should be renderer
#include "qmapdataproxy.h"

QT_DATAVIS3D_BEGIN_NAMESPACE

MapRenderItem::MapRenderItem()
    : BarRenderItem()
{
}

MapRenderItem::~MapRenderItem()
{
}

void MapRenderItem::formatLabel()
{
    // TODO The label format specified in proxy should probably have additional custom formatting
    // TODO specifiers in addition to standard printf specifiers for placement of item labels
    // TODO and selection data (like row/column in bar selection)

    // Format the string on first access
    QString numStr;
    numStr.setNum(m_value);
    // TODO actually format instead of just prepending the value
    m_label.clear(); // Just in case
    m_label.append(m_itemLabel);
    m_label.append(QStringLiteral(" "));
    m_label.append(numStr);
    m_label.append(m_renderer->dataProxy()->itemLabelFormat());
}

QT_DATAVIS3D_END_NAMESPACE
