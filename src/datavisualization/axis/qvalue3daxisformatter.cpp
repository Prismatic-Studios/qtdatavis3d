/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
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

#include "qvalue3daxisformatter_p.h"
#include "qvalue3daxis_p.h"

QT_BEGIN_NAMESPACE_DATAVISUALIZATION

/*!
 * \class QValue3DAxisFormatter
 * \inmodule QtDataVisualization
 * \brief QValue3DAxisFormatter is base class for value axis formatters.
 * \since Qt Data Visualization 1.1
 *
 * This class provides formatting rules for a linear QValue3DAxis. Subclass it if you
 * want to implement custom value axes.
 *
 * The base class has no public API beyond constructors and destructors. It is meant to be only
 * used internally. However, subclasses may implement public properties as needed.
 *
 * \sa QLog3DAxisFormatter
 */

/*!
 * \qmltype ValueAxis3DFormatter
 * \inqmlmodule QtDataVisualization
 * \since QtDataVisualization 1.1
 * \ingroup datavisualization_qml
 * \instantiates QValue3DAxisFormatter
 * \brief ValueAxis3DFormatter is base type for value axis formatters.
 *
 * This type provides formatting rules for a linear ValueAxis3D.
 * This type is the default type for ValueAxis3D and thus never needs to be explicitly created.
 * This type has not public functionality.
 */

/*!
 * \internal
 */
QValue3DAxisFormatter::QValue3DAxisFormatter(QValue3DAxisFormatterPrivate *d, QObject *parent) :
    QObject(parent),
    d_ptr(d)
{
}

/*!
 * Constructs a new QValue3DAxisFormatter instance with optional \a parent.
 */
QValue3DAxisFormatter::QValue3DAxisFormatter(QObject *parent) :
    QObject(parent),
    d_ptr(new QValue3DAxisFormatterPrivate(this))
{
}

/*!
 * Destroys QValue3DAxisFormatter.
 */
QValue3DAxisFormatter::~QValue3DAxisFormatter()
{
}

/*!
 * \return \c true if negative values are valid values for parent axis.
 * The default implementation always returns true.
 */
bool QValue3DAxisFormatter::allowNegatives() const
{
    return true;
}

/*!
 * \return \c true if zero is a valid value for parent axis.
 * The default implementation always returns true.
 */
bool QValue3DAxisFormatter::allowZero() const
{
    return true;
}

/*!
 * Creates a new empty instance of this formatter. Must be reimplemented in a subclass.
 *
 * \return the new instance. The renderer uses this method to cache a copy of the
 * the formatter. The ownership of the new copy transfers to the caller.
 */
QValue3DAxisFormatter *QValue3DAxisFormatter::createNewInstance() const
{
    return new QValue3DAxisFormatter();
}

/*!
 * This method populates the label and grid line position arrays, as well as calculates
 * any values needed for mapping between value and position. It is allowed to access
 * the parent axis from inside this function.
 *
 * This method must be reimplemented in a subclass.
 *
 * See gridPositions(), subGridPositions(), and labelPositions() documentation about the arrays
 * that need to be populated.
 *
 * \sa gridPositions(), subGridPositions(), labelPositions(), axis()
 */
void QValue3DAxisFormatter::recalculate()
{
    d_ptr->doRecalculate();
}

/*!
 * Reimplement this method in a subclass to resolve the formatted string for a given \a value
 * if the default formatting provided by QValue3DAxis::labelFormat property is not sufficient.
 *
 * \return the formatted label string using \a value and \a format.
 *
 * \sa recalculate(), stringForValue(), QValue3DAxis::labelFormat
 */
QString QValue3DAxisFormatter::stringForValue(float value, const QString &format) const
{
    return d_ptr->stringForValue(value, format);
}

/*!
 * Reimplement this method if the position cannot be resolved by linear interpolation
 * between the parent axis minimum and maximum values.
 *
 * \return the normalized position along the axis for the given \a value.
 * The returned value should be between 0.0 (for minimum value) and 1.0 (for maximum value),
 * inclusive, if the value is within the parent axis range.
 *
 * \sa doRecalculate(), positionAt()
 */
float QValue3DAxisFormatter::positionAt(float value) const
{
    return d_ptr->positionAt(value);
}

/*!
 * Reimplement this method if the value cannot be resolved by linear interpolation
 * between the parent axis minimum and maximum values.
 *
 * \return the value at the normalized \a position along the axis.
 * The \a position value should be between 0.0 (for minimum value) and 1.0 (for maximum value),
 * inclusive to obtain values within the parent axis range.
 *
 * \sa doRecalculate(), positionAt()
 */
float QValue3DAxisFormatter::valueAt(float position) const
{
    return d_ptr->valueAt(position);
}

/*!
 * Copies all relevant values from this formatter to the \a copy.
 * When reimplementing this method in a subclass, call the the superclass version at some point.
 * The renderer uses this method to cache a copy of the the formatter.
 *
 * \return the new copy. The ownership of the new copy transfers to the caller.
 */
void QValue3DAxisFormatter::populateCopy(QValue3DAxisFormatter &copy) const
{
    d_ptr->doPopulateCopy(*(copy.d_ptr.data()));
}

/*!
 * Marks this formatter dirty, prompting the renderer to make a new copy of its cache on the next
 * renderer synchronization. This method should be called by a subclass whenever the formatter
 * is changed in a way that affects the resolved values.
 */
void QValue3DAxisFormatter::markDirty()
{
    d_ptr->markDirty();
}

/*!
 * \return the parent axis. The parent axis must only be accessed in recalculate()
 * method to maintain thread safety in environments using a threaded renderer.
 *
 * \sa recalculate()
 */
QValue3DAxis *QValue3DAxisFormatter::axis() const
{
    return d_ptr->m_axis;
}

/*!
 * \return Returns a reference to the array of normalized grid positions.
 * The array size is equal to the segment count of the parent axis plus one.
 * The values should be between 0.0 (for minimum value) and 1.0 (for maximum value), inclusive.
 * The grid line at the index zero corresponds to the minimum value of the axis.
 */
QVector<float> &QValue3DAxisFormatter::gridPositions() const
{
    return d_ptr->m_gridPositions;
}

/*!
 * \return Returns a reference to the array of normalized subgrid positions.
 * The array size is equal to segment count of tha parent axis times subsegment count of the parent
 * axis minus one.
 * The values should be between 0.0 (for minimum value) and 1.0 (for maximum value), inclusive.
 */
QVector<QVector<float> > &QValue3DAxisFormatter::subGridPositions() const
{
    return d_ptr->m_subGridPositions;
}

/*!
 * \return Returns a reference to the array of normalized label positions.
 * The array size is equal to the segment count of the parent axis plus one.
 * The values should be between 0.0 (for minimum value) and 1.0 (for maximum value), inclusive.
 * The label at the index zero corresponds to the minimum value of the axis.
 */
QVector<float> &QValue3DAxisFormatter::labelPositions() const
{
    return d_ptr->m_labelPositions;
}

// QValue3DAxisFormatterPrivate
QValue3DAxisFormatterPrivate::QValue3DAxisFormatterPrivate(QValue3DAxisFormatter *q)
    : QObject(0),
      q_ptr(q),
      m_needsRecalculate(true),
      m_min(0.0f),
      m_max(0.0f),
      m_rangeNormalizer(0.0f),
      m_axis(0),
      m_preparsedParamType(Utils::ParamTypeUnknown)
{
}

QValue3DAxisFormatterPrivate::~QValue3DAxisFormatterPrivate()
{
}

void QValue3DAxisFormatterPrivate::recalculate()
{
    // Only recalculate if we need to and have m_axis pointer. If we do not have
    // m_axis, either we are not attached to an axis or this is a renderer cache.
    if (m_axis && m_needsRecalculate)
        q_ptr->recalculate();
}

void QValue3DAxisFormatterPrivate::doRecalculate()
{
    m_needsRecalculate = false;

    m_gridPositions.clear();
    m_subGridPositions.clear();
    m_labelPositions.clear();

    int segmentCount = m_axis->segmentCount();
    int subGridCount = m_axis->subSegmentCount() - 1;
    m_min = m_axis->min();
    m_max = m_axis->max();
    m_rangeNormalizer = (m_max - m_min);

    m_gridPositions.resize(segmentCount + 1);

    float segmentStep = 1.0f / float(segmentCount);
    float subSegmentStep = 0;

    if (subGridCount > 0) {
        subSegmentStep = segmentStep / (subGridCount + 1);
        m_subGridPositions.resize(segmentCount);
        for (int i = 0; i < segmentCount; i++)
            m_subGridPositions[i].resize(subGridCount);
    }

    m_labelPositions.resize(segmentCount + 1);

    // Calculate positions

    for (int i = 0; i < segmentCount; i++) {
        float gridValue = segmentStep * i;
        m_gridPositions[i] = gridValue;
        m_labelPositions[i] = gridValue;
        if (m_subGridPositions.size()) {
            for (int j = 0; j < subGridCount; j++)
                m_subGridPositions[i][j] = gridValue + subSegmentStep * (j + 1);
        }
    }

    // Ensure max value doesn't suffer from any rounding errors
    m_gridPositions[segmentCount] = 1.0f;
    m_labelPositions[segmentCount] = 1.0f;
}

void QValue3DAxisFormatterPrivate::populateCopy(QValue3DAxisFormatter &copy)
{
    recalculate();
    q_ptr->populateCopy(copy);
}

void QValue3DAxisFormatterPrivate::doPopulateCopy(QValue3DAxisFormatterPrivate &copy)
{
    copy.m_min = m_min;
    copy.m_max = m_max;
    copy.m_rangeNormalizer = m_rangeNormalizer;

    copy.m_gridPositions = m_gridPositions;
    copy.m_labelPositions = m_labelPositions;
    copy.m_subGridPositions = m_subGridPositions;
}

QString QValue3DAxisFormatterPrivate::stringForValue(float value, const QString &format)
{
    if (m_previousLabelFormat.compare(format)) {
        // Format string different than the previous one used, reparse it
        m_previousLabelFormat = format;
        m_preparsedParamType = Utils::findFormatParamType(format);
        m_labelFormatArray = format.toUtf8();
    }

    return Utils::formatLabel(m_labelFormatArray, m_preparsedParamType, value);
}

float QValue3DAxisFormatterPrivate::positionAt(float value) const
{
    return ((value - m_min) / m_rangeNormalizer);
}

float QValue3DAxisFormatterPrivate::valueAt(float position) const
{
    return ((position * m_rangeNormalizer) + m_min);
}

void QValue3DAxisFormatterPrivate::setAxis(QValue3DAxis *axis)
{
    Q_ASSERT(axis);

    connect(axis, &QValue3DAxis::segmentCountChanged,
            this, &QValue3DAxisFormatterPrivate::markDirty);
    connect(axis, &QValue3DAxis::subSegmentCountChanged,
            this, &QValue3DAxisFormatterPrivate::markDirty);
    connect(axis, &QAbstract3DAxis::rangeChanged,
            this, &QValue3DAxisFormatterPrivate::markDirty);

    m_axis = axis;
}

void QValue3DAxisFormatterPrivate::markDirty()
{
    m_needsRecalculate = true;
    if (m_axis && m_axis->orientation() != QAbstract3DAxis::AxisOrientationNone)
        emit m_axis->dptr()->formatterDirty();
}

QT_END_NAMESPACE_DATAVISUALIZATION