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

#include "qitemmodelsurfacedatamapping_p.h"

QT_DATAVISUALIZATION_BEGIN_NAMESPACE

/*!
 * \class QItemModelSurfaceDataMapping
 * \inmodule QtDataVisualization
 * \brief Data model mapping for Q3DSurface.
 * \since 1.0.0
 *
 * QItemModelSurfaceDataMapping is used to map roles of QAbstractItemModel to rows, columns, and values
 * of Q3DSurface. There are three ways to use QItemModelSurfaceDataMapping:
 *
 * 1) If useModelCategories property is set to true, QItemModelSurfaceDataMapping will map rows and
 *    columns of QAbstractItemModel to rows and columns of Q3DSurface, and uses the value returned for
 *    Qt::DisplayRole as bar value by default.
 *    The value role to be used can be redefined if Qt::DisplayRole is not suitable.
 *
 * 2) For models that do not have data already neatly sorted into rows and columns, such as
 *    QAbstractListModel based models, you can define a role from the model to map for each of row,
 *    column and value.
 *
 * 3) If you do not want to include all data contained in the model, or the autogenerated rows and
 *    columns are not ordered as you wish, you can specify which rows and columns should be included
 *    and in which order by defining an explicit list of categories for either or both of rows and
 *    columns.
 *
 *    For example, assume that you have a custom QAbstractItemModel storing surface topography data.
 *    Each item in the model has roles "longitude", "latitude" and "height". The item model already
 *    contains the data properly sorted so that longitudes and latitudes are first encountered in
 *    correct order, which enables us to utilize the row and column category autogeneration.
 *    You could do the following to display the data in a surface graph:
 *
 *    \snippet doc_src_qtdatavisualization.cpp 5
 *
 * \sa QItemModelSurfaceDataProxy
 */

/*!
 * \qmltype SurfaceDataMapping
 * \instantiates QItemModelSurfaceDataMapping
 *
 * This type is used to map roles of AbstractItemModel to rows, columns, and values of Surface3D.
 * For more complete description, see QItemModelSurfaceDataMapping.
 *
 * Usage example:
 *
 * \snippet doc_src_qmldatavisualization.cpp 6
 *
 * \sa ItemModelSurfaceDataProxy
 */

/*!
 * \qmlproperty string SurfaceDataMapping::rowRole
 * The row role of the mapping.
 */

/*!
 * \qmlproperty string SurfaceDataMapping::columnRole
 * The column role of the mapping.
 */

/*!
 * \qmlproperty string SurfaceDataMapping::valueRole
 * The value role of the mapping.
 */

/*!
 * \qmlproperty list SurfaceDataMapping::rowCategories
 * The row categories of the mapping.
 */

/*!
 * \qmlproperty list SurfaceDataMapping::columnCategories
 * The column categories of the mapping.
 */

/*!
 * \qmlproperty list SurfaceDataMapping::useModelCategories
 * When set to true, the mapping ignores row and column roles and categories, and uses
 * the rows and columns from the model instead. Defaults to false.
 */

/*!
 * \qmlproperty list SurfaceDataMapping::autoRowCategories
 * When set to true, the mapping ignores any explicitly set row categories
 * and overwrites them with automatically generated ones whenever the
 * data from model is resolved. Proxy minimum and maximum row values are also
 * autogenerated from data when this is set to true. Defaults to true.
 */

/*!
 * \qmlproperty list SurfaceDataMapping::autoColumnCategories
 * When set to true, the mapping ignores any explicitly set column categories
 * and overwrites them with automatically generated ones whenever the
 * data from model is resolved. Proxy minimum and maximum column values are also
 * autogenerated from data when this is set to true. Defaults to true.
 */

/*!
 * Constructs QItemModelSurfaceDataMapping with the given \a parent.
 */
QItemModelSurfaceDataMapping::QItemModelSurfaceDataMapping(QObject *parent)
    : QAbstractDataMapping(new QItemModelSurfaceDataMappingPrivate(this), parent)
{
}

/*!
 * Constructs QItemModelSurfaceDataMapping with \a valueRole and the given \a parent.
 * This constructor is meant to be used with models that have data properly sorted
 * in rows and columns already, so it also sets useModelCategories property to true.
 */
QItemModelSurfaceDataMapping::QItemModelSurfaceDataMapping(const QString &valueRole, QObject *parent)
    : QAbstractDataMapping(new QItemModelSurfaceDataMappingPrivate(this), parent)
{
    dptr()->m_valueRole = valueRole;
    dptr()->m_useModelCategories = true;
}

/*!
 * Constructs QItemModelSurfaceDataMapping with \a rowRole, \a columnRole, \a valueRole
 * and the given \a parent.
 */
QItemModelSurfaceDataMapping::QItemModelSurfaceDataMapping(const QString &rowRole,
                                                   const QString &columnRole,
                                                   const QString &valueRole,
                                                   QObject *parent)
    : QAbstractDataMapping(new QItemModelSurfaceDataMappingPrivate(this), parent)
{
    dptr()->m_rowRole = rowRole;
    dptr()->m_columnRole = columnRole;
    dptr()->m_valueRole = valueRole;
}

/*!
 * Constructs QItemModelSurfaceDataMapping with \a rowRole, \a columnRole, \a valueRole,
 * \a rowCategories, \a columnCategories and the given \a parent. This constructor
 * also sets autoRowCategories and autoColumnCategories to false.
 */
QItemModelSurfaceDataMapping::QItemModelSurfaceDataMapping(const QString &rowRole,
                                                           const QString &columnRole,
                                                           const QString &valueRole,
                                                           const QStringList &rowCategories,
                                                           const QStringList &columnCategories,
                                                           QObject *parent)
    : QAbstractDataMapping(new QItemModelSurfaceDataMappingPrivate(this), parent)
{
    dptr()->m_rowRole = rowRole;
    dptr()->m_columnRole = columnRole;
    dptr()->m_valueRole = valueRole;
    dptr()->m_rowCategories = rowCategories;
    dptr()->m_columnCategories = columnCategories;
    dptr()->m_autoRowCategories = false;
    dptr()->m_autoColumnCategories = false;
}

/*!
 * Destroys QItemModelSurfaceDataMapping.
 */
QItemModelSurfaceDataMapping::~QItemModelSurfaceDataMapping()
{
}

/*!
 * \property QItemModelSurfaceDataMapping::rowRole
 *
 * Defines the row role for the mapping.
 */
void QItemModelSurfaceDataMapping::setRowRole(const QString &role)
{
    if (dptr()->m_rowRole != role) {
        dptr()->m_rowRole = role;
        emit mappingChanged();
    }
}

QString QItemModelSurfaceDataMapping::rowRole() const
{
    return dptrc()->m_rowRole;
}

/*!
 * \property QItemModelSurfaceDataMapping::columnRole
 *
 * Defines the column role for the mapping.
 */
void QItemModelSurfaceDataMapping::setColumnRole(const QString &role)
{
    if (dptr()->m_columnRole != role) {
        dptr()->m_columnRole = role;
        emit mappingChanged();
    }
}

QString QItemModelSurfaceDataMapping::columnRole() const
{
    return dptrc()->m_columnRole;
}

/*!
 * \property QItemModelSurfaceDataMapping::valueRole
 *
 * Defines the value role for the mapping.
 */
void QItemModelSurfaceDataMapping::setValueRole(const QString &role)
{
    if (dptr()->m_valueRole != role) {
        dptr()->m_valueRole = role;
        emit mappingChanged();
    }
}

QString QItemModelSurfaceDataMapping::valueRole() const
{
    return dptrc()->m_valueRole;
}

/*!
 * \property QItemModelSurfaceDataMapping::rowCategories
 *
 * Defines the row categories for the mapping.
 */
void QItemModelSurfaceDataMapping::setRowCategories(const QStringList &categories)
{
    if (dptr()->m_rowCategories != categories) {
        dptr()->m_rowCategories = categories;
        emit mappingChanged();
    }
}

QStringList QItemModelSurfaceDataMapping::rowCategories() const
{
    return dptrc()->m_rowCategories;
}

/*!
 * \property QItemModelSurfaceDataMapping::columnCategories
 *
 * Defines the column categories for the mapping.
 */
void QItemModelSurfaceDataMapping::setColumnCategories(const QStringList &categories)
{
    if (dptr()->m_columnCategories != categories) {
        dptr()->m_columnCategories = categories;
        emit mappingChanged();
    }
}

QStringList QItemModelSurfaceDataMapping::columnCategories() const
{
    return dptrc()->m_columnCategories;
}

/*!
 * \property QItemModelSurfaceDataMapping::useModelCategories
 *
 * When set to true, the mapping ignores row and column roles and categories, and uses
 * the rows and columns from the model instead. Defaults to false.
 */
void QItemModelSurfaceDataMapping::setUseModelCategories(bool enable)
{
    if (dptr()->m_useModelCategories != enable) {
        dptr()->m_useModelCategories = enable;
        emit mappingChanged();
    }
}

bool QItemModelSurfaceDataMapping::useModelCategories() const
{
    return dptrc()->m_useModelCategories;
}

/*!
 * \property QItemModelSurfaceDataMapping::autoRowCategories
 *
 * When set to true, the mapping ignores any explicitly set row categories
 * and overwrites them with automatically generated ones whenever the
 * data from model is resolved. Proxy minimum and maximum row values are also
 * autogenerated from data when this is set to true. Defaults to true.
 */
void QItemModelSurfaceDataMapping::setAutoRowCategories(bool enable)
{
    if (dptr()->m_autoRowCategories != enable) {
        dptr()->m_autoRowCategories = enable;
        emit mappingChanged();
    }
}

bool QItemModelSurfaceDataMapping::autoRowCategories() const
{
    return dptrc()->m_autoRowCategories;
}

/*!
 * \property QItemModelSurfaceDataMapping::autoColumnCategories
 *
 * When set to true, the mapping ignores any explicitly set column categories
 * and overwrites them with automatically generated ones whenever the
 * data from model is resolved. Proxy minimum and maximum column values are also
 * autogenerated from data when this is set to true. Defaults to true.
 */
void QItemModelSurfaceDataMapping::setAutoColumnCategories(bool enable)
{
    if (dptr()->m_autoColumnCategories != enable) {
        dptr()->m_autoColumnCategories = enable;
        emit mappingChanged();
    }
}

bool QItemModelSurfaceDataMapping::autoColumnCategories() const
{
    return dptrc()->m_autoColumnCategories;
}

/*!
 * Changes \a rowRole, \a columnRole, \a valueRole, \a rowCategories and \a columnCategories to the
 * mapping.
 */
void QItemModelSurfaceDataMapping::remap(const QString &rowRole,
                                         const QString &columnRole,
                                         const QString &valueRole,
                                         const QStringList &rowCategories,
                                         const QStringList &columnCategories)
{
    dptr()->m_rowRole = rowRole;
    dptr()->m_columnRole = columnRole;
    dptr()->m_valueRole = valueRole;
    dptr()->m_rowCategories = rowCategories;
    dptr()->m_columnCategories = columnCategories;

    emit mappingChanged();
}

/*!
 * /return index of the specified \a category in row categories list.
 * If the row categories list is empty, -1 is returned.
 * \note If the automatic row categories generation is in use, this method will
 * not return valid index before the data in the model is resolved for the first time.
 */
int QItemModelSurfaceDataMapping::rowCategoryIndex(const QString &category)
{
    return dptr()->m_rowCategories.indexOf(category);
}

/*!
 * /return index of the specified \a category in column categories list.
 * \note If the automatic column categories generation is in use, this method will
 * not return valid index before the data in the model is resolved for the first time.
 */
int QItemModelSurfaceDataMapping::columnCategoryIndex(const QString &category)
{
    return dptr()->m_columnCategories.indexOf(category);
}

/*!
 * \internal
 */
QItemModelSurfaceDataMappingPrivate *QItemModelSurfaceDataMapping::dptr()
{
    return static_cast<QItemModelSurfaceDataMappingPrivate *>(d_ptr.data());
}

/*!
 * \internal
 */
const QItemModelSurfaceDataMappingPrivate *QItemModelSurfaceDataMapping::dptrc() const
{
    return static_cast<const QItemModelSurfaceDataMappingPrivate *>(d_ptr.data());
}

// QItemModelSurfaceDataMappingPrivate

QItemModelSurfaceDataMappingPrivate::QItemModelSurfaceDataMappingPrivate(QItemModelSurfaceDataMapping *q)
    : QAbstractDataMappingPrivate(q, QAbstractDataProxy::DataTypeSurface),
    m_useModelCategories(false),
    m_autoRowCategories(true),
    m_autoColumnCategories(true)
{
}

QItemModelSurfaceDataMappingPrivate::~QItemModelSurfaceDataMappingPrivate()
{
}


QT_DATAVISUALIZATION_END_NAMESPACE

