#pragma once

#include "utils/qt_misc.h"
#include "utils/CuLogger.h"
#include "utils/CuJSONObject.h"
#include "utils/CuStringMatcher.h"
#include "utils/CuPairList.h"
#include "widgets/CuWebView.h"
#include "widgets/CuTabButton.h"
#include "widgets/CuUrlEdit.h"
#include "objects/CuSchemeHandler.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    public:
        MainWindow(const QList<QString> &args);
        ~MainWindow();

    protected:
        void closeEvent(QCloseEvent* event) override;

    private:
        QWidget* baseWidget_;
        QVBoxLayout* baseLayout_;
        QHBoxLayout* controlBarLayout_;
        CuUrlEdit* urlEdit_;
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
        void LoadUrl_(const QUrl &url);
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
        void PrintPageToPdf_();
};
