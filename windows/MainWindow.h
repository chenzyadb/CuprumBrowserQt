#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include "utils/CuLogger.h"
#include "utils/JsonObject.h"

#include <QApplication>
#include <QCoreApplication>
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QWebEngineProfile>
#include <QWebEngineSettings>
#include <QDir>
#include <QFile>
#include <QCloseEvent>
#include <QResizeEvent>
#include <QMenu>
#include <QAction>
#include <QWebEngineDownloadRequest>
#include <QFileDialog>
#include <QProgressDialog>
#include <QDialog>
#include <QMessageBox>
#include <QStandardPaths>
#include "widgets/CuWebView.h"
#include "widgets/CuTabButton.h"
#include "objects/CuSchemeHandler.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    public:
        MainWindow(const QString &path);
        ~MainWindow();

    private:
        CuLogger* logger_;
        QString path_;
        QWebEngineProfile* browserProfile_;

        QWidget* baseWidget_;
        QVBoxLayout* baseLayout_;
        QHBoxLayout* controlBarLayout_;
        QLineEdit* urlEdit_;
        QPushButton* loadButton_;
        QPushButton* backButton_;
        QPushButton* forwardButton_;
        QPushButton* reflashButton_;
        QPushButton* menuButton_;
        QHBoxLayout* browserTabLayout_;
        QPushButton* addButton_;
        std::unordered_map<CuTabButton*, CuWebView*> buttonToWindow_;
        std::unordered_map<CuWebView*, CuTabButton*> windowToButton_;
        CuWebView* topBrowserWindow_;
        QMenu* browserMenu_;

        void AddBrowserWindow_(CuWebView* browserWindow);
        void LoadUrl_(const QString &url);
        void GoBack_();
        void GoForward_();
        void Reflash_();
        void SetPageZoomIn_();
        void SetPageZoomOut_();
        void ResetPageZoom_();
        void OpenDevTool_();
        void AddBookmark_();
        void OpenAboutPage_();

    private slots:
        void Browser_onUrlChanged(const QUrl &url);
        void Browser_onTitleChanged(const QString &title);
        void Browser_onIconChanged(const QIcon &icon);
        void Browser_onNewWindowCreated(CuWebView* newBrowserWindow);
        void Browser_onDownloadRequested(QWebEngineDownloadRequest* request);
        void ChangeTopWindow_(CuTabButton* tabButton);
        void RemoveBrowserWindow_(CuTabButton* tabButton);

    protected:
        void resizeEvent(QResizeEvent* event) override;
        void closeEvent(QCloseEvent* event) override;
};
