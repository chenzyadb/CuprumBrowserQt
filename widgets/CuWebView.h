#pragma once

#include <QObject>
#include <QWidget>
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QWebEngineProfile>
#include <QContextMenuEvent>
#include <QWebEngineFullScreenRequest>

class CuWebView : public QWebEngineView
{
    Q_OBJECT
    public:
        explicit CuWebView(QWidget* parent, QWebEngineProfile* profile);
        ~CuWebView();

    signals:
        void NewWindowCreated(CuWebView* newBrowserWindow);

    private:
        QWidget* parent_;
        QWebEngineProfile* profile_;

    protected:
        CuWebView* createWindow(QWebEnginePage::WebWindowType type) override;
        void closeEvent(QCloseEvent* event) override;
};
