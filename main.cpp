#include "utils/qt_misc.h"
#include "utils/CuLogger.h"
#include "windows/MainWindow.h"

int main(int argc, char *argv[])
{
    CU::Logger::Create(CU::Logger::LogLevel::VERBOSE, GetRePrevString(argv[0], "\\") + "\\debug.log");
    CU::Logger::Info("CuprumBrowser V1 (%d) by chenzyadb.", GetCompileDateCode());

    QWebEngineUrlScheme browserScheme("cu");
    browserScheme.setSyntax(QWebEngineUrlScheme::Syntax::HostAndPort);
    browserScheme.setDefaultPort(8000);
    browserScheme.setFlags(
        QWebEngineUrlScheme::SecureScheme |
        QWebEngineUrlScheme::LocalAccessAllowed |
        QWebEngineUrlScheme::ViewSourceAllowed |
        QWebEngineUrlScheme::ContentSecurityPolicyIgnored |
        QWebEngineUrlScheme::CorsEnabled);
    QWebEngineUrlScheme::registerScheme(browserScheme);

    QApplication app(argc, argv);
    app.setAttribute(Qt::AA_PluginApplication, false);
    app.setAttribute(Qt::AA_DontShowIconsInMenus, true);
    app.setAttribute(Qt::AA_NativeWindows, false);
    app.setAttribute(Qt::AA_DontCreateNativeWidgetSiblings, true);
    app.setAttribute(Qt::AA_DontUseNativeMenuBar, true);
    app.setAttribute(Qt::AA_DontUseNativeDialogs, true);
    app.setAttribute(Qt::AA_UseDesktopOpenGL, true);
    app.setAttribute(Qt::AA_UseOpenGLES, true);
    app.setAttribute(Qt::AA_UseSoftwareOpenGL, false);
    app.setAttribute(Qt::AA_ShareOpenGLContexts, true);
    app.setAttribute(Qt::AA_UseStyleSheetPropagationInWidgetStyles, true);
    CU::Logger::Info("Application Created.");

    auto window = new MainWindow();
    window->show();

    int appRet = app.exec();
    CU::Logger::Info("Application closed, return %d.", appRet);
    return appRet;
}
