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

//! [1]
#include <QtDataVisualization/qutils.h>
//! [1]

#include <QtGui/QGuiApplication>
#include <QtCore/QDir>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlEngine>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickView viewer;

    // Enable antialiasing
    //! [0]
    viewer.setFormat(QtDataVisualization::qDefaultSurfaceFormat());
    //! [0]

    // The following are needed to make examples run without having to install the module
    // in desktop environments.
#ifdef Q_OS_WIN
    QString extraImportPath(QStringLiteral("%1/../../../../%2"));
#else
    QString extraImportPath(QStringLiteral("%1/../../../%2"));
#endif
    viewer.engine()->addImportPath(extraImportPath.arg(QGuiApplication::applicationDirPath(),
                                      QString::fromLatin1("qml")));
    //! [4]
    QObject::connect(viewer.engine(), &QQmlEngine::quit, &viewer, &QWindow::close);
    //! [4]

    viewer.setTitle(QStringLiteral("QML scatter example"));

    //! [3]
    viewer.setSource(QUrl("qrc:/qml/qmlscatter/main.qml"));
    //! [3]

    viewer.setResizeMode(QQuickView::SizeRootObjectToView);

    //! [2]
    viewer.showMaximized();
    //! [2]

    return app.exec();
}