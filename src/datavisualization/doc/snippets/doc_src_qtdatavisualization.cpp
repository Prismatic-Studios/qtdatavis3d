/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the QtDataVisualization module.
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
#include <QtDataVisualization>
//! [0]

//! [1]
proxy->setItemLabelFormat(QStringLiteral("@valueTitle for (@rowLabel, @colLabel): %.1f"));
//! [1]

//! [2]
proxy->setItemLabelFormat(QStringLiteral("@xTitle: @xValue, @yTitle: @yValue, @zTitle: @zValue"));
//! [2]

//! [3]
// By defining row and column categories, you tell the mapping which row and column each item
// belongs to. The categories must match the data stored in the model in the roles you define
// for row and column mapping. In this example we expect "year" role to return four digit year
// and "month" to return three letter designation for the month.
//
// An example of an item in model would be:
// Requested role -> Returned data
// "year" -> "2006" // Matches the first row category, so this item is added to the first row.
// "month" -> "jan" // Matches the first column category, so this item is added as first item in the row.
// "income" -> "12.1"
// "expenses" -> "9.2"
QStringList years;
QStringList months;
years << "2006" << "2007" << "2008" << "2009" << "2010" << "2011" << "2012";
months << "jan" << "feb" << "mar" << "apr" << "may" << "jun" << "jul" << "aug" << "sep" << "oct" << "nov" << "dec";

QItemModelBarDataMapping *mapping = new QItemModelBarDataMapping(QStringLiteral("year"), // Row role
                                                                 QStringLiteral("month"), // Column role
                                                                 QStringLiteral("income"), // Value role
                                                                 years, // Row categories
                                                                 months); // Column categories

QItemModelBarDataProxy *proxy = new QItemModelBarDataProxy(customModel, mapping);

//...

// To display different data later, you can simply change the mapping of the current
// mapping object, or set another mapping object.
proxy->activeMapping()->setValueRole(QStringLiteral("expenses"));
//! [3]

//! [4]
// Map "density" value to X-axis, "hardness" to Y-axis and "conductivity" to Z-axis.
QItemModelScatterDataMapping *mapping = new QItemModelScatterDataMapping(QStringLiteral("density"),
                                                                         QStringLiteral("hardness"),
                                                                         QStringLiteral("conductivity"))

QItemModelScatterDataProxy *proxy = new QItemModelScatterDataProxy(customModel, mapping);
//! [4]

//! [5]
QItemModelSurfaceDataMapping *mapping = new QItemModelSurfaceDataMapping(QStringLiteral("longitude"), // Row role
                                                                         QStringLiteral("latitude"), // Column role
                                                                         QStringLiteral("height")); // value role

QItemModelSurfaceDataProxy *proxy = new QItemModelSurfaceDataProxy(customModel, mapping);
//! [5]