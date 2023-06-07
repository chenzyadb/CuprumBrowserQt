#include <iostream>
#include <exception>
#include "utils/CuLogger.h"
#include "utils/utils.h"

#include <QCoreApplication>
#include <QApplication>
#include <QWebEngineUrlScheme>
#include "windows/MainWindow.h"

int main(int argc, char *argv[])
{
    QString path = GetRePrevStringQt(argv[0], '\\');
    CuLogger::CreateLogger(CuLogger::LOG_DEBUG, path.toStdString() + "\\debug.log");
    const auto &logger = CuLogger::GetLogger();
    logger->Info("CuprumBrowser V1 (%d) by chenzyadb.", GetCompileDateCode(__DATE__));

    QWebEngineUrlScheme browserScheme = QWebEngineUrlScheme("cu");
    browserScheme.setSyntax(QWebEngineUrlScheme::Syntax::HostAndPort);
    browserScheme.setDefaultPort(8000);
    browserScheme.setFlags(
        QWebEngineUrlScheme::SecureScheme |
        QWebEngineUrlScheme::LocalAccessAllowed |
        QWebEngineUrlScheme::ViewSourceAllowed |
        QWebEngineUrlScheme::ContentSecurityPolicyIgnored |
        QWebEngineUrlScheme::CorsEnabled);
    QWebEngineUrlScheme::registerScheme(browserScheme);

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);
    QApplication app(argc, argv);
    logger->Info("Application Created.");

    MainWindow* mainWindow = new MainWindow(path);
    mainWindow->show();

    int appExecRet = app.exec();
    logger->Info("Application exited, return %d.", appExecRet);
    return appExecRet;
}
