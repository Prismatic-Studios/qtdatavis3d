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

#include "topographicseries.h"

#include <QDebug>

using namespace QtDataVisualization;

// Value used to encode height data as RGB value on PNG file
const float packingFactor = 11983.0f;

TopographicSeries::TopographicSeries()
{
    setDrawMode(QSurface3DSeries::DrawSurface);
    setFlatShadingEnabled(true);
}

TopographicSeries::~TopographicSeries()
{
}

void TopographicSeries::setTopographyFile(const QString file, float width, float height)
{
    QImage heightMapImage(file);
    uchar *bits = heightMapImage.bits();
    int imageHeight = heightMapImage.height();
    int imageWidth = heightMapImage.width();
    int widthBits = imageWidth * 4;
    float stepX = width / float(imageWidth);
    float stepZ = height / float(imageHeight);

    QSurfaceDataArray *dataArray = new QSurfaceDataArray;
    dataArray->reserve(imageHeight);
    for (int i = 0; i < imageHeight; i++) {
        int p = (imageHeight - 1 - i) * widthBits;
        QSurfaceDataRow *newRow = new QSurfaceDataRow(imageWidth);
        for (int j = 0; j < imageWidth; j++) {
            uchar aa = bits[p + 0];
            uchar rr = bits[p + 1];
            uchar gg = bits[p + 2];
            uint color = uint((gg << 16) + (rr << 8) + aa);
            float y = float(color) / packingFactor;
            (*newRow)[j].setPosition(QVector3D(float(j) * stepX, y, float(i) * stepZ));
            p = p + 4;
        }
        *dataArray << newRow;
    }

    m_sampleCountX = float(imageWidth);
    m_sampleCountZ = float(imageHeight);

    dataProxy()->resetArray(dataArray);
}