/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the documentation of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "q3dbars.h"
#include "qdataset.h"

#include <QGuiApplication>
#include <QTimer>
#include <QDebug>

//#define CYCLE_THROUGH_STYLES
//#define CYCLE_THROUGH_PRESET_CAMERAS
//#define CYCLE_THROUGH_THEMES
#define USE_STATIC_DATA

using namespace QtDataVis3D;

class ChartDataGenerator : public QObject
{
public:
    explicit ChartDataGenerator(Q3DBars *barchart);
    ~ChartDataGenerator();

    void addDataSet();
    void addBars();
    void changeStyle();
    void changePresetCamera();
    void changeTheme();
    void start();

private:
    Q3DBars *m_chart;
    QTimer *m_dataTimer;
    QTimer *m_styleTimer;
    QTimer *m_presetTimer;
    QTimer *m_themeTimer;
    int m_columnCount;
    int m_rowCount;
};

ChartDataGenerator::ChartDataGenerator(Q3DBars *barchart)
    : m_chart(barchart)
    , m_dataTimer(0)
    , m_styleTimer(0)
    , m_presetTimer(0)
    , m_themeTimer(0)
    , m_columnCount(9)
    , m_rowCount(9)
{
    // Set up bar specifications; make the bars as wide as they are deep,
    // and add a small space between the bars
    m_chart->setBarSpecs(QPointF(1.0f, 1.0f), QPointF(0.2f, 0.2f), true);

#ifndef USE_STATIC_DATA
    // Set up sample space; make it as deep as it's wide
    m_chart->setupSampleSpace(QPoint(m_columnCount, m_rowCount));
#endif

    // Set bar type to smooth bar
#ifndef CYCLE_THROUGH_STYLES
    m_chart->setBarType(Q3DBars::Bars, false);
#endif

    // Set selection mode to full
    m_chart->setSelectionMode(Q3DBars::BarRowAndColumn);

#ifndef CYCLE_THROUGH_THEMES
    // Set bar colors
    m_chart->setBarColor(QColor(Qt::black), QColor(Qt::red), QColor(Qt::darkBlue));
#endif

    // Set preset camera position
    m_chart->setCameraPreset(Q3DBars::PresetFront);
}

ChartDataGenerator::~ChartDataGenerator()
{
    if (m_dataTimer) {
        m_dataTimer->stop();
        delete m_dataTimer;
    }
    if (m_styleTimer) {
        m_styleTimer->stop();
        delete m_styleTimer;
    }
    if (m_presetTimer) {
        m_presetTimer->stop();
        delete m_presetTimer;
    }
    if (m_themeTimer) {
        m_themeTimer->stop();
        delete m_themeTimer;
    }
    delete m_chart;
}

void ChartDataGenerator::start()
{
#ifndef USE_STATIC_DATA
    m_dataTimer = new QTimer();
    m_dataTimer->setTimerType(Qt::CoarseTimer);
    m_dataTimer->setInterval(100);
    QObject::connect(m_dataTimer, &QTimer::timeout, this, &ChartDataGenerator::addBars);
    m_dataTimer->start(100);
#else
    addDataSet();
#endif

#ifdef CYCLE_THROUGH_STYLES
    // Change bar style every 10 seconds
    m_styleTimer = new QTimer();
    m_styleTimer->setTimerType(Qt::CoarseTimer);
    m_styleTimer->setInterval(10000);
    QObject::connect(m_styleTimer, &QTimer::timeout, this, &ChartDataGenerator::changeStyle);
    m_styleTimer->start(10000);
#endif

#ifdef CYCLE_THROUGH_PRESET_CAMERAS
    // Change preset camera every 5 seconds
    m_presetTimer = new QTimer();
    m_presetTimer->setTimerType(Qt::CoarseTimer);
    m_presetTimer->setInterval(5000);
    QObject::connect(m_presetTimer, &QTimer::timeout, this
                     , &ChartDataGenerator::changePresetCamera);
    m_presetTimer->start(5000);
#endif

#ifdef CYCLE_THROUGH_THEMES
    // Change theme every 2 seconds
    m_themeTimer = new QTimer();
    m_themeTimer->setTimerType(Qt::CoarseTimer);
    m_themeTimer->setInterval(3000);//2000);
    QObject::connect(m_themeTimer, &QTimer::timeout, this
                     , &ChartDataGenerator::changeTheme);
    m_themeTimer->start(3000);//2000);
#endif
}

void ChartDataGenerator::addDataSet()
{
#if 1
    // Prepare data to be visualized
    // Use float vector adder
    QVector< QVector<float> > data;
    QVector<float> row;
    // TODO: Keep here for testing
    for (int j = 0; j < m_rowCount; j++) {
        for (int i = 0; i < m_columnCount; i++) {
            row.prepend(((float)i / (float)m_columnCount) * 100 + (float)(rand() % 30));
            //row.prepend(1.0f);
        }
        data.prepend(row);
        row.clear();
    }
    // Set up sample space based on inserted data
    m_chart->setupSampleSpace(QPoint(m_columnCount, m_rowCount));
    // Add data to chart
    m_chart->addDataSet(data);
#else
    // Prepare data to be visualized
    // Use QDataSet adder

    // Set window title
    m_chart->setWindowTitle(QStringLiteral("Hours playing banjo"));

    // Set up row and column names
    QVector<QString> days;
    days << "Monday" << "Tuesday" << "Wednesday" << "Thursday" << "Friday" << "Saturday" << "Sunday";
    QVector<QString> weeks;
    weeks << "week 1" << "week 2" << "week 3" << "week 4" << "week 5";

    // Set up data
    float hours[5][7] = {{2, 1, 3, 0, 1, 5, 7}
                        , {0, 1, 3, 1, 2, 2, 3}
                        , {1, 1, 2, 1, 4, 4, 4}
                        , {0, 0, 0, 0, 2, 2, 0}
                        , {3, 3, 6, 2, 2, 1, 1}};

    // Create data set
    QDataSet *dataSet = new QDataSet();

    // Add labels
    dataSet->setLabels("Day of week", "Week of year", "Hours doing something", weeks, days);

    // Create data rows
    QDataRow *dataRow;
    for (int week = 0; week < weeks.size(); week++) {
        dataRow = new QDataRow(weeks.at(week));
        // Create data items
        for (int day = 0; day < days.size(); day++) {
            // Add data to rows
            dataRow->addItem(new QDataItem(hours[week][day], "hours," + days.at(day)));
        }
        // Add row to set
        dataSet->addRow(dataRow);
        // Get next pointer
        dataRow++;
    }

    // Set up sample space based on prepared data
    m_chart->setupSampleSpace(QPoint(days.size(), weeks.size()));

    // Add data to chart
    m_chart->addDataSet(dataSet);
#endif
}

void ChartDataGenerator::addBars()
{
    QVector<float> data;
    for (int i = 0; i < m_columnCount; i++) {
        data.append(((float)i / (float)m_columnCount) / 2.0f + (float)(rand() % 30) / 100);
    }
    m_chart->addDataRow(data);
}

void ChartDataGenerator::changeStyle()
{
    static int model = 0;
    switch (model) {
    case 0:
        m_chart->setBarType(Q3DBars::Cylinders, false);
        break;
    case 1:
        m_chart->setBarType(Q3DBars::Cylinders, true);
        break;
    case 2:
        m_chart->setBarType(Q3DBars::Cones, false);
        break;
    case 3:
        m_chart->setBarType(Q3DBars::Cones, true);
        break;
    case 4:
        m_chart->setBarType(Q3DBars::Bars, false);
        break;
    case 5:
        m_chart->setBarType(Q3DBars::Bars, true);
        break;
    case 6:
        m_chart->setBarType(Q3DBars::Pyramids, false);
        break;
    case 7:
        m_chart->setBarType(Q3DBars::Pyramids, true);
        break;
    }
    model++;
    if (model > 7)
        model = 0;
}

void ChartDataGenerator::changePresetCamera()
{
    static int preset = 0;

    m_chart->setCameraPreset((Q3DBars::CameraPreset)preset);

    if (++preset > (int)Q3DBars::PresetDirectlyAboveCCW45)
        preset = 0;
}

void ChartDataGenerator::changeTheme()
{
    static int theme = 1; // TODO: System theme not yet implemented

    m_chart->setTheme((Q3DBars::ColorTheme)theme);

    if (++theme > (int)Q3DBars::ThemeLight)
        theme = 1; // TODO: System theme not yet implemented
}

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    Q3DBars barchart;
    barchart.resize(800, 600);
    barchart.show();

    ChartDataGenerator *generator = new ChartDataGenerator(&barchart);
    generator->start();

    return app.exec();
}