#pragma once

#include "utils/qt_misc.h"
#include "utils/browser_misc.h"
#include "objects/CuSchemeHandler.h"

class CuWebView : public QWebEngineView
{
    Q_OBJECT
    public:
        static QWebEngineProfile* GetWebEngineProfile_();

        explicit CuWebView(QWidget* parent = nullptr);
        ~CuWebView();

    signals:
        void NewWindowCreated(CuWebView* newBrowserWindow);

    protected:
        CuWebView* createWindow(QWebEnginePage::WebWindowType type) override;
        void closeEvent(QCloseEvent* event) override;
};
