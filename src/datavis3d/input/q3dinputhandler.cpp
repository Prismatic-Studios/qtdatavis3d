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
#include "q3dinputhandler.h"

QT_DATAVIS3D_BEGIN_NAMESPACE

Q3DInputHandler::Q3DInputHandler() :
    QAbstract3DInputHandler()
{
}

// Input event listeners
void Q3DInputHandler::mousePressEvent(QMouseEvent *event, const QPoint &mousePos)
{
    QRect mainViewPort = mainViewPortRect();
    if (Qt::LeftButton == event->button()) {
        if (slicingActivated()) {
            if (mousePos.x() <= mainViewPort.width()
                    && mousePos.y() <= mainViewPort.height()) {
                setInputState(QDataVis::InputOnOverview);
                //qDebug() << "Mouse pressed on overview";
            } else {
                setInputState(QDataVis::InputOnSlice);
                //qDebug() << "Mouse pressed on zoom";
            }
        } else {
            setInputState(QDataVis::InputOnScene);
            // update mouse positions to prevent jumping when releasing or repressing a button
            setInputPosition(mousePos);
            //qDebug() << "Mouse pressed on scene";
        }
    } else if (Qt::MiddleButton == event->button()) {
        // reset rotations
        setInputPosition(QPoint(0, 0));
    } else if (!slicingActivated() && Qt::RightButton == event->button()) {
        // disable rotating when in slice view
        setInputState(QDataVis::InputRotating);
        // update mouse positions to prevent jumping when releasing or repressing a button
        setInputPosition(mousePos);
    }
    // TODO: Call actual camera class when it's been written.
    //m_cameraHelper->updateMousePos(m_mousePos);}
}

void Q3DInputHandler::mouseReleaseEvent(QMouseEvent *event, const QPoint &mousePos)
{
    Q_UNUSED(event);
    if (QDataVis::InputRotating == inputState()) {
        // update mouse positions to prevent jumping when releasing or repressing a button
        setInputPosition(mousePos);
        // TODO: Call actual camera class when it's been written.
        //m_cameraHelper->updateMousePos(mousePos);
    }
    setInputState(QDataVis::InputNone);

}

void Q3DInputHandler::mouseMoveEvent(QMouseEvent *event, const QPoint &mousePos)
{
    Q_UNUSED(event);
    if (QDataVis::InputRotating == inputState())
        setInputPosition(mousePos);
}

void Q3DInputHandler::wheelEvent(QWheelEvent *event)
{
    // disable zooming if in slice view
    if (slicingActivated())
        return;

    // Adjust zoom level based on what zoom range we're in.
    int zoomLevel = QAbstract3DInputHandler::zoomLevel();
    if (zoomLevel > oneToOneZoomLevel)
        zoomLevel += event->angleDelta().y() / nearZoomRangeDivider;
    else if (zoomLevel > halfSizeZoomLevel)
        zoomLevel += event->angleDelta().y() / midZoomRangeDivider;
    else
        zoomLevel += event->angleDelta().y() / farZoomRangeDivider;
    if (zoomLevel > maxZoomLevel)
        zoomLevel = maxZoomLevel;
    else if (zoomLevel < minZoomLevel)
        zoomLevel = minZoomLevel;

    setZoomLevel(zoomLevel);
}

QT_DATAVIS3D_END_NAMESPACE