#pragma once

#include "utils/qt_misc.h"
#include "utils/CuLogger.h"
#include "utils/CuJSONObject.h"
#include "utils/CuStringMatcher.h"
#include "utils/CuPairList.h"
#include "widgets/CuWebView.h"
#include "widgets/CuTabButton.h"
#include "objects/CuSchemeHandler.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    public:
        MainWindow();
        ~MainWindow();

    protected:
        void closeEvent(QCloseEvent* event) override;

    private:
        CU::StringMatcher urlMatcher_;
        QWidget* baseWidget_;
        QVBoxLayout* baseLayout_;
        QHBoxLayout* controlBarLayout_;
        QLineEdit* urlEdit_;
        QPushButton* loadButton_;
        QPushButton* backButton_;
        QPushButton* forwardButton_;
        QPushButton* refreshButton_;
        QPushButton* menuButton_;
        QHBoxLayout* browserTabLayout_;
        QPushButton* addButton_;
        CU::PairList<CuTabButton*, CuWebView*> buttonWindowPairs_;
        CuWebView* topBrowserWindow_;
        QMenu* browserMenu_;

        void AddBrowserWindow_(CuWebView* browserWindow);
        void LoadUrl_(const QString &url);
        void GoBack_();
        void GoForward_();
        void Refresh_();
        void SetPageZoomIn_();
        void SetPageZoomOut_();
        void ResetPageZoom_();
        void OpenDevTool_();
        void AddBookmark_();

    private slots:
        void ChangeTopWindow_(CuTabButton* tabButton);
        void RemoveBrowserWindow_(CuTabButton* tabButton);
        void onDownloadRequested_(QWebEngineDownloadRequest* request);
        void FindPageText_();
};
