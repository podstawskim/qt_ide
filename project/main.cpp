#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "documenthandler.h"
#include "linenumbers.h"
#include "compiler.h"
#include <QAbstractItemModel>
#include <QFileSystemWatcher>
#include <QFileSystemModel>
#include <QQmlContext>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QFileSystemModel>
#include <QDateTime>
#include <QDesktopServices>
#include <QUrl>
#include <QQuickView>
#include <QDirModel>
#include "textformat.h"
#include "syntaxhighlighter.h"

int main(int argc, char ** argv)
  {
    #if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    //QGuiApplication app(argc, argv);
    QApplication app(argc, argv);
    qmlRegisterType<DocumentHandler>("pl.ide", 1, 0, "DocumentHandler");
    qmlRegisterType<LineNumbers>("pl.ide", 1, 0, "LineNumbers");
    qmlRegisterType<Compiler>("pl.ide", 1, 0, "Compiler");
    qmlRegisterType<TextFormat>("pl.ide", 1,0,"TextFormat");
    qmlRegisterType<SyntaxHighlighter>("pl.ide",1,0,"SyntaxHighlighter");

    QQmlApplicationEngine engine;

    QFileSystemModel *fsm = new QFileSystemModel(&engine);
    fsm->setRootPath(QDir::homePath());
    //fsm->setRootPath(".");
    fsm->setResolveSymlinks(true);
    engine.rootContext()->setContextProperty("fileSystemModel", fsm);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                       &app, [url](QObject *obj, const QUrl &objUrl) {
    if (!obj && url == objUrl)
              QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
  }
