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

//! [0]
#include <QtDataVis3D>
//! [0]

//! [1]
proxy->setItemLabelFormat(QStringLiteral("@valueTitle for (@rowLabel, @colLabel): %.1f"));
//! [1]

//! [2]
proxy->setItemLabelFormat(QStringLiteral("@xTitle: @xValue, @yTitle: @yValue, @zTitle: @zValue"));
//! [2]
