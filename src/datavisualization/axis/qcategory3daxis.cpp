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

#include "qcategory3daxis.h"
#include "qcategory3daxis_p.h"
#include "bars3dcontroller_p.h"
#include "qbardataproxy.h"

QT_DATAVISUALIZATION_BEGIN_NAMESPACE

/*!
 * \class QCategory3DAxis
 * \inmodule QtDataVisualization
 * \brief The QCategory3DAxis class is used for manipulating an axis of a graph.
 * \since Qt Data Visualization 1.0
 *
 * QCategory3DAxis provides an axis that can be given labels. The axis is divided into equal-sized
 * categories based on the data window size defined by setting the axis range.
 *
 * Grid lines are drawn between categories, if visible. Labels are drawn to positions of categories
 * if provided.
 */

/*!
 * \qmltype CategoryAxis3D
 * \inqmlmodule QtDataVisualization
 * \since QtDataVisualization 1.0
 * \ingroup datavisualization_qml
 * \instantiates QCategory3DAxis
 * \inherits AbstractAxis3D
 * \brief The CategoryAxis3D type is used for manipulating an axis of a graph.
 *
 * This type provides an axis that can be given labels.
 */

/*!
 * \qmlproperty list CategoryAxis3D::labels
 *
 * Defines labels for axis applied to categories. If there are fewer labels than categories, the
 * remaining ones do not have a label. If category labels are not defined explicitly, labels are
 * generated from the data row (or column) labels.
 *
 * \note If the graph has multiple visible series and category labels are not defined explicitly,
 * changing the rows (or columns) on any of the attached series will regenerate the labels.
 */

/*!
 * Constructs QCategory3DAxis with \a parent.
 */
QCategory3DAxis::QCategory3DAxis(QObject *parent) :
    QAbstract3DAxis(new QCategory3DAxisPrivate(this), parent)
{
    connect(this, &QCategory3DAxis::labelsChanged, this, &QAbstract3DAxis::labelsChanged);
}

/*!
 * Destroys QCategory3DAxis.
 */
QCategory3DAxis::~QCategory3DAxis()
{
}

/*!
 * \property QCategory3DAxis::labels
 *
 * Defines labels for axis applied to categories. If there are fewer labels than categories, the
 * remaining ones do not have a label. If category labels are not defined explicitly, labels are
 * generated from the data row (or column) labels.
 *
 * \note If the graph has multiple visible series and category labels are not defined explicitly,
 * changing the rows (or columns) on any of the attached series will regenerate the labels.
 */
QStringList QCategory3DAxis::labels() const
{
    return QAbstract3DAxis::labels();
}

void QCategory3DAxis::setLabels(const QStringList &labels)
{
    dptr()->m_labelsExplicitlySet = !labels.isEmpty();
    bool labelsFromData = false;

    // Get labels from data proxy if axis is attached to a bar controller and an active axis there
    if (labels.isEmpty()) {
        Bars3DController *controller = qobject_cast<Bars3DController *>(parent());
        if (controller) {
            if (controller->axisX() == this) {
                controller->handleDataRowLabelsChanged();
                labelsFromData = true;
            } else if (controller->axisZ() == this) {
                controller->handleDataColumnLabelsChanged();
                labelsFromData = true;
            }
        }
    }

    if (!labelsFromData && d_ptr->m_labels != labels) {
        d_ptr->m_labels = labels;
        emit labelsChanged();
    }
}

/*!
 * \internal
 */
QCategory3DAxisPrivate *QCategory3DAxis::dptr()
{
    return static_cast<QCategory3DAxisPrivate *>(d_ptr.data());
}

QCategory3DAxisPrivate::QCategory3DAxisPrivate(QCategory3DAxis *q)
    : QAbstract3DAxisPrivate(q, QAbstract3DAxis::AxisTypeCategory),
      m_labelsExplicitlySet(false)
{
    m_onlyPositiveValues = true;
    m_allowMinMaxSame = true;
}

QCategory3DAxisPrivate::~QCategory3DAxisPrivate()
{
}

/*!
 * \internal
 * Controller uses this function to set labels from data proxy as category labels.
 * If the labels have been set explicitly by the user, data proxy labels are not used.
 */
void QCategory3DAxisPrivate::setDataLabels(const QStringList &labels)
{
    if (!m_labelsExplicitlySet && m_labels != labels) {
        m_labels = labels;
        emit qptr()->labelsChanged();
    }
}

QCategory3DAxis *QCategory3DAxisPrivate::qptr()
{
    return static_cast<QCategory3DAxis *>(q_ptr);
}

QT_DATAVISUALIZATION_END_NAMESPACE