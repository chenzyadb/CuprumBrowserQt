#include "MainWindow.h"

constexpr char windowStyle[] =
    "MainWindow {                                                                "
    "   background-color: #FFFFFF;                                               "
    "}                                                                           "
    "QPushButton {                                                               "
    "   border: none;                                                            "
    "   background-color: #FFFFFF;                                               "
    "   color: #000000;                                                          "
    "   border-radius: 5px;                                                      "
    "}                                                                           "
    "QPushButton:hover {                                                         "
    "   background-color: #F0F0F0;                                               "
    "}                                                                           "
    "QPushButton:pressed {                                                       "
    "   background-color: #E8E8E8;                                               "
    "}                                                                           "
    "QPushButton::menu-indicator {                                               "
    "   width: 0;                                                                "
    "   height: 0;                                                               "
    "}                                                                           "
    "QMenu {                                                                     "
    "   background-color: #F8F8F8;                                               "
    "   padding: 5px;                                                            "
    "}                                                                           "
    "QMenu::item {                                                               "
    "   border-radius: 5px;                                                      "
    "   padding: 5px;                                                            "
    "   background-color: #F8F8F8;                                               "
    "   font-size: 12px;                                                         "
    "   color: #000000;                                                          "
    "}                                                                           "
    "QMenu::item:selected {                                                      "
    "   background-color: #E8E8E8;                                               "
    "}                                                                           "
    "QMenu::item:pressed {                                                       "
    "   background-color: #E0E0E0;                                               "
    "}                                                                           ";


MainWindow::MainWindow(const QList<QString> &args) :
    QMainWindow(),
    baseWidget_(nullptr),
    baseLayout_(nullptr),
    controlBarLayout_(nullptr),
    urlEdit_(nullptr),
    loadButton_(nullptr),
    backButton_(nullptr),
    forwardButton_(nullptr),
    refreshButton_(nullptr),
    menuButton_(nullptr),
    browserTabLayout_(nullptr),
    addButton_(nullptr),
    buttonWindowPairs_(),
    topBrowserWindow_(nullptr),
    browserMenu_(nullptr)
{
    resize(1000, 600);
    setMinimumSize(800, 500);
    setWindowIcon(QIcon(":/res/media/cu_icon.ico"));
    setWindowTitle("CuprumBrowserQt");
    setStyleSheet(windowStyle);
    {
        baseWidget_ = new QWidget(this);
        this->setCentralWidget(baseWidget_);
    }
    {
        baseLayout_ = new QVBoxLayout();
        baseLayout_->setAlignment(Qt::AlignLeft | Qt::AlignTop);
        baseLayout_->setContentsMargins(0, 0, 0, 0);
        baseLayout_->setSpacing(2);
        baseWidget_->setLayout(baseLayout_);
    }
    {
        controlBarLayout_ = new QHBoxLayout();
        controlBarLayout_->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        controlBarLayout_->setContentsMargins(4, 4, 4, 0);
        controlBarLayout_->setSpacing(2);
        baseLayout_->addLayout(controlBarLayout_);
    }
    {
        backButton_ = new QPushButton(baseWidget_);
        backButton_->setFixedSize(30, 30);
        backButton_->setIcon(QIcon(":/res/media/back.png"));
        backButton_->setIconSize(QSize(20, 20));
        backButton_->setContentsMargins(0, 0, 0, 0);
        backButton_->setToolTip("Go back.");
        connect(backButton_, &QPushButton::clicked, this, [this]() {
            GoBack_();
        });
        controlBarLayout_->addWidget(backButton_);
    }
    {
        forwardButton_ = new QPushButton(baseWidget_);
        forwardButton_->setFixedSize(30, 30);
        forwardButton_->setIcon(QIcon(":/res/media/forward.png"));
        forwardButton_->setIconSize(QSize(20, 20));
        forwardButton_->setContentsMargins(0, 0, 0, 0);
        forwardButton_->setToolTip("Go forward.");
        connect(forwardButton_, &QPushButton::clicked, this, [this]() {
            GoForward_();
        });
        controlBarLayout_->addWidget(forwardButton_);
    }
    {
        refreshButton_ = new QPushButton(baseWidget_);
        refreshButton_->setFixedSize(30, 30);
        refreshButton_->setIcon(QIcon(":/res/media/refresh.png"));
        refreshButton_->setIconSize(QSize(20, 20));
        refreshButton_->setContentsMargins(0, 0, 0, 0);
        refreshButton_->setToolTip("Refresh page.");
        connect(refreshButton_, &QPushButton::clicked, this, [this]() {
            Refresh_();
        });
        controlBarLayout_->addWidget(refreshButton_);
    }
    {
        urlEdit_ = new CuUrlEdit(baseWidget_);
        urlEdit_->setMinimumHeight(30);
        urlEdit_->setMaximumHeight(30);
        urlEdit_->setContentsMargins(0, 0, 0, 0);
        urlEdit_->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        urlEdit_->setToolTip("Invoke search or enter a URL.");
        urlEdit_->setPlaceholderText("Invoke search or enter a URL");
        connect(urlEdit_, &QLineEdit::returnPressed, this, [this]() {
            auto url = QUrl::fromUserInput(urlEdit_->text());
            if (url.isValid() && url.toString().contains('.')) {
                LoadUrl_(url);
            } else {
                LoadUrl_(QUrl::fromUserInput(QString("https://www.baidu.com/s?wd=") + urlEdit_->text()));
            }
        });
        controlBarLayout_->addWidget(urlEdit_);
    }
    {
        menuButton_ = new QPushButton(baseWidget_);
        menuButton_->setFixedSize(30, 30);
        menuButton_->setIcon(QIcon(":/res/media/menu.png"));
        menuButton_->setIconSize(QSize(20, 20));
        menuButton_->setContentsMargins(0, 0, 0, 0);
        menuButton_->setToolTip("Browser menu.");
        controlBarLayout_->addWidget(menuButton_);
    }
    {
        browserTabLayout_ = new QHBoxLayout();
        browserTabLayout_->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        browserTabLayout_->setContentsMargins(4, 4, 4, 4);
        browserTabLayout_->setSpacing(4);
        baseLayout_->addLayout(browserTabLayout_);
    }
    {
        addButton_ = new QPushButton(baseWidget_);
        addButton_->setFixedSize(30, 30);
        addButton_->setIcon(QIcon(":/res/media/add.png"));
        addButton_->setIconSize(QSize(20, 20));
        addButton_->setContentsMargins(0, 0, 0, 0);
        addButton_->setToolTip("Add Tab.");
        connect(addButton_, &QPushButton::clicked, this, [this]() {
            AddBrowserWindow_(new CuWebView(baseWidget_));
            LoadUrl_(QUrl("cu://home/"));
        });
        browserTabLayout_->addWidget(addButton_);
    }
    {
        browserMenu_ = new QMenu(menuButton_);
        browserMenu_->setFixedWidth(200);
        {
            auto addTap = new QAction(browserMenu_);
            addTap->setShortcuts(QKeySequence::AddTab);
            addTap->setText("添加标签页");
            connect(addTap, &QAction::triggered, this, [this]() {
                AddBrowserWindow_(new CuWebView(baseWidget_));
                LoadUrl_(QUrl("cu://home/"));
            });
            browserMenu_->addAction(addTap);
        }
        {
            auto removeTab = new QAction(browserMenu_);
            removeTab->setShortcut(QKeySequence("Ctrl+X"));
            removeTab->setText("关闭当前标签页");
            connect(removeTab, &QAction::triggered, this, [this]() {
                RemoveBrowserWindow_(buttonWindowPairs_(topBrowserWindow_));
            });
            browserMenu_->addAction(removeTab);
        }
        browserMenu_->addSeparator();
        {
            auto openHomePage = new QAction(browserMenu_);
            openHomePage->setShortcut(QKeySequence("Ctrl+H"));
            openHomePage->setText("打开首页");
            connect(openHomePage, &QAction::triggered, this, [this](){
                LoadUrl_(QUrl("cu://home/"));
            });
            browserMenu_->addAction(openHomePage);
        }
        {
            auto openBookmark = new QAction(browserMenu_);
            openBookmark->setShortcut(QKeySequence("Ctrl+B"));
            openBookmark->setText("打开书签页");
            connect(openBookmark, &QAction::triggered, this, [this](){
                LoadUrl_(QUrl("cu://bookmarks/"));
            });
            browserMenu_->addAction(openBookmark);
        }
        {
            auto openHistory = new QAction(browserMenu_);
            openHistory->setShortcut(QKeySequence("Ctrl+J"));
            openHistory->setText("打开历史记录");
            connect(openHistory, &QAction::triggered, this, [this]() {
                LoadUrl_(QUrl("cu://history/"));
            });
            browserMenu_->addAction(openHistory);
        }
        browserMenu_->addSeparator();
        {
            auto addBookmark = new QAction(browserMenu_);
            addBookmark->setShortcut(QKeySequence("Ctrl+D"));
            addBookmark->setText("将此页加入书签");
            connect(addBookmark, &QAction::triggered, this, [this](){
                AddBookmark_();
            });
            browserMenu_->addAction(addBookmark);
        }
        {
            auto findPageText = new QAction(browserMenu_);
            findPageText->setShortcut(QKeySequence("Ctrl+F"));
            findPageText->setText("查找页面内容");
            connect(findPageText, &QAction::triggered, this, &MainWindow::FindPageText_);
            browserMenu_->addAction(findPageText);
        }
        {
            auto zoomIn = new QAction(browserMenu_);
            zoomIn->setShortcuts(QKeySequence::ZoomIn);
            zoomIn->setText("放大当前页面");
            connect(zoomIn, &QAction::triggered, this, [this](){
                SetPageZoomIn_();
            });
            browserMenu_->addAction(zoomIn);
        }
        {
            auto zoomOut = new QAction(browserMenu_);
            zoomOut->setShortcuts(QKeySequence::ZoomOut);
            zoomOut->setText("缩小当前页面");
            connect(zoomOut, &QAction::triggered, this, [this](){
                SetPageZoomOut_();
            });
            browserMenu_->addAction(zoomOut);
        }
        {
            auto resetZoom = new QAction(browserMenu_);
            resetZoom->setShortcut(QKeySequence("Ctrl+R"));
            resetZoom->setText("还原当前页面缩放");
            connect(resetZoom, &QAction::triggered, this, [this](){
                ResetPageZoom_();
            });
            browserMenu_->addAction(resetZoom);
        }
        {
            auto printToPdf = new QAction(browserMenu_);
            printToPdf->setShortcut(QKeySequence("Ctrl+P"));
            printToPdf->setText("打印网页为PDF");
            connect(printToPdf, &QAction::triggered, this, &MainWindow::PrintPageToPdf_);
            browserMenu_->addAction(printToPdf);
        }
        {
            auto openDevTool = new QAction(browserMenu_);
            openDevTool->setShortcut(QKeySequence("F12"));
            openDevTool->setText("打开开发人员工具");
            connect(openDevTool, &QAction::triggered, this, [this](){
                OpenDevTool_();
            });
            browserMenu_->addAction(openDevTool);
        }
        browserMenu_->addSeparator();
        {
            auto aboutQt = new QAction(browserMenu_);
            aboutQt->setText("关于Qt");
            connect(aboutQt, &QAction::triggered, this, []() { 
                QApplication::aboutQt();
            });
            browserMenu_->addAction(aboutQt);
        }
        {
            auto aboutBrowser = new QAction(browserMenu_);
            aboutBrowser->setText("关于浏览器");
            connect(aboutBrowser, &QAction::triggered, this, [this]() {
                LoadUrl_(QUrl("cu://about/"));
            });
            browserMenu_->addAction(aboutBrowser);
        }
        {
            auto quitBrowser = new QAction(browserMenu_);
            quitBrowser->setShortcut(QKeySequence("Ctrl+Q"));
            quitBrowser->setText("退出");
            connect(quitBrowser, &QAction::triggered, this, [this](){
                close();
            });
            browserMenu_->addAction(quitBrowser);
        }
        menuButton_->setMenu(browserMenu_);
    }
    {
        connect(CuWebView::GetWebEngineProfile_(), &QWebEngineProfile::downloadRequested, this, &MainWindow::onDownloadRequested_);
        AddBrowserWindow_(new CuWebView(baseWidget_));
        if (args.size() > 1) {
            LoadUrl_(QUrl::fromUserInput(args[1]));
        } else {
            LoadUrl_(QUrl("cu://home/"));
        }
    }
}

MainWindow::~MainWindow() { }

void MainWindow::closeEvent(QCloseEvent* event)
{
    BookmarkProvider::SaveToDisk();
    HistoryProvider::SaveToDisk();
    auto profile = CuWebView::GetWebEngineProfile_();
    profile->clearAllVisitedLinks();
    profile->clearHttpCache();
    event->accept();
    deleteLater();
}

void MainWindow::AddBrowserWindow_(CuWebView* newBrowserWindow)
{
    if (topBrowserWindow_ != nullptr) {
        topBrowserWindow_->setEnabled(false);
        topBrowserWindow_->setVisible(false);
        buttonWindowPairs_(topBrowserWindow_)->setFocus(false);
    }

    auto newTabButton = new CuTabButton(baseWidget_);
    buttonWindowPairs_.add(newTabButton, newBrowserWindow);
    newTabButton->setFocus(true);
    newTabButton->setIcon(newBrowserWindow->icon());
    newTabButton->setText(newBrowserWindow->title());
    connect(newTabButton, &CuTabButton::onClick, this, &MainWindow::ChangeTopWindow_);
    connect(newTabButton, &CuTabButton::onCommandClose, this, &MainWindow::RemoveBrowserWindow_);
    browserTabLayout_->removeWidget(addButton_);
    browserTabLayout_->addWidget(newTabButton);
    browserTabLayout_->addWidget(addButton_);

    connect(newBrowserWindow, &CuWebView::urlChanged, this, [this, newBrowserWindow](const QUrl &url) {
        if (topBrowserWindow_ == newBrowserWindow) {
            urlEdit_->setText(url.toString());
            urlEdit_->setCursorPosition(0);
        }
    });
    connect(newBrowserWindow, &CuWebView::titleChanged, this, [this, newBrowserWindow, newTabButton](const QString &title) {
        if (topBrowserWindow_ == newBrowserWindow) {
            setWindowTitle("CuprumBrowserQt - " + title);
        }
        newTabButton->setText(title);
    });
    connect(newBrowserWindow, &CuWebView::iconChanged, this, [newTabButton](const QIcon &icon) {
        newTabButton->setIcon(icon);
    });
    connect(newBrowserWindow, &CuWebView::NewWindowCreated, this, [this, newBrowserWindow](CuWebView* newWindow) {
        if (!buttonWindowPairs_.containsValue(newWindow)) {
            AddBrowserWindow_(newWindow);
        }
    });
    baseLayout_->addWidget(newBrowserWindow);
    setWindowTitle("CuprumBrowserQt - " + newBrowserWindow->title());
    urlEdit_->setText(newBrowserWindow->url().toString());
    urlEdit_->setCursorPosition(0);

    topBrowserWindow_ = newBrowserWindow;
}

void MainWindow::LoadUrl_(const QUrl &url)
{
    if (topBrowserWindow_ != nullptr) {
        topBrowserWindow_->setUrl(url);
    }
}

void MainWindow::GoBack_()
{
    if (topBrowserWindow_ != nullptr) {
        topBrowserWindow_->back();
    }
}

void MainWindow::GoForward_()
{
    if (topBrowserWindow_ != nullptr) {
        topBrowserWindow_->forward();
    }
}

void MainWindow::Refresh_()
{
    if (topBrowserWindow_ != nullptr) {
        topBrowserWindow_->reload();
    }
}

void MainWindow::SetPageZoomIn_()
{
    if (topBrowserWindow_ != nullptr) {
        auto zoomFactor = topBrowserWindow_->zoomFactor();
        if (zoomFactor < 2.0) {
            topBrowserWindow_->setZoomFactor(zoomFactor + 0.1);
        }
    }
}

void MainWindow::SetPageZoomOut_()
{
    if (topBrowserWindow_ != nullptr) {
        auto zoomFactor = topBrowserWindow_->zoomFactor();
        if (zoomFactor > 0.5) {
            topBrowserWindow_->setZoomFactor(zoomFactor - 0.1);
        }
    }
}

void MainWindow::ResetPageZoom_()
{
    if (topBrowserWindow_ != nullptr) {
        topBrowserWindow_->setZoomFactor(1.0);
    }
}

void MainWindow::OpenDevTool_()
{
    if (topBrowserWindow_ != nullptr) {
        auto devToolView = new CuWebView(baseWidget_);
        topBrowserWindow_->page()->triggerAction(QWebEnginePage::InspectElement);
        topBrowserWindow_->page()->setDevToolsPage(devToolView->page());
        AddBrowserWindow_(devToolView);
    }
}

void MainWindow::AddBookmark_()
{
    if (topBrowserWindow_ != nullptr) {
        BookmarkProvider::AddBookmark(topBrowserWindow_->url(), topBrowserWindow_->title());
    }
}

void MainWindow::ChangeTopWindow_(CuTabButton* tabButton)
{
    auto newTopWindow = buttonWindowPairs_.atKey(tabButton);
    if (newTopWindow == topBrowserWindow_) {
        return;
    }

    if (topBrowserWindow_ != nullptr) {
        topBrowserWindow_->setEnabled(false);
        topBrowserWindow_->setVisible(false);
        buttonWindowPairs_(topBrowserWindow_)->setFocus(false);
    }
    newTopWindow->setEnabled(true);
    newTopWindow->setVisible(true);

    setWindowTitle("CuprumBrowserQt - " + newTopWindow->title());
    urlEdit_->setText(newTopWindow->url().toString());
    urlEdit_->setCursorPosition(0);
    tabButton->setIcon(newTopWindow->icon());
    tabButton->setText(newTopWindow->title());
    tabButton->setFocus(true);
    topBrowserWindow_ = newTopWindow;
}

void MainWindow::RemoveBrowserWindow_(CuTabButton* tabButton)
{
    auto removeWindow = buttonWindowPairs_.atKey(tabButton);
    if (buttonWindowPairs_.size() == 1) {
        close();
        return;
    }

    buttonWindowPairs_.removeKey(tabButton);
    if (removeWindow == topBrowserWindow_) {
        auto newTopWindow = buttonWindowPairs_.back().second;
        newTopWindow->setEnabled(true);
        newTopWindow->setVisible(true);
        auto newTabButton = buttonWindowPairs_(newTopWindow);
        newTabButton->setIcon(newTopWindow->icon());
        newTabButton->setText(newTopWindow->title());
        newTabButton->setFocus(true);
        setWindowTitle("CuprumBrowserQt - " + newTopWindow->title());
        urlEdit_->setText(newTopWindow->url().toString());
        urlEdit_->setCursorPosition(0);
        topBrowserWindow_ = newTopWindow;
    }

    baseLayout_->removeWidget(removeWindow);
    removeWindow->close();
    removeWindow->deleteLater();

    browserTabLayout_->removeWidget(tabButton);
    disconnect(tabButton, &CuTabButton::onClick, this, &MainWindow::ChangeTopWindow_);
    disconnect(tabButton, &CuTabButton::onCommandClose, this, &MainWindow::RemoveBrowserWindow_);
    tabButton->deleteLater();
}

void MainWindow::onDownloadRequested_(QWebEngineDownloadRequest* request)
{
    if (QMessageBox::question(nullptr, "获取到下载请求", QString("确定要下载 ") + request->suggestedFileName() + " 文件吗?",
                              QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        auto downloadPath = CuWebView::GetWebEngineProfile_()->downloadPath();
        downloadPath = QFileDialog::getExistingDirectory(nullptr, "选择下载目录", downloadPath, QFileDialog::ShowDirsOnly);
        request->setDownloadDirectory(downloadPath);
        int totalMegaBytes = static_cast<int>(request->totalBytes() / 1024 / 1024);
        auto downloadProgressDialog = new QProgressDialog("文件开始下载", "取消", 0, totalMegaBytes, nullptr);
        downloadProgressDialog->setWindowModality(Qt::NonModal);
        downloadProgressDialog->setAutoClose(true);
        downloadProgressDialog->setAutoReset(false);
        downloadProgressDialog->setValue(0);
        downloadProgressDialog->setFixedSize(360, 120);
        downloadProgressDialog->show();
        connect(request, &QWebEngineDownloadRequest::receivedBytesChanged, this,
                [this, request, downloadProgressDialog, totalMegaBytes]() {
                    int receivedMegaBytes = static_cast<int>(request->receivedBytes() / 1024 / 1024);
                    auto labelText = CU::Format("文件下载中, 已下载的数据: {}/{} MB.", receivedMegaBytes, totalMegaBytes);
                    downloadProgressDialog->setLabelText(labelText.c_str());
                    downloadProgressDialog->setValue(receivedMegaBytes);
                    if (downloadProgressDialog->wasCanceled()) {
                        request->cancel();
                        downloadProgressDialog->close();
                        downloadProgressDialog->deleteLater();
                    }
        });
        connect(request, &QWebEngineDownloadRequest::isFinishedChanged, this, [this, request, downloadProgressDialog]() {
            if (request->state() == QWebEngineDownloadRequest::DownloadCompleted) {
                downloadProgressDialog->close();
                downloadProgressDialog->deleteLater();
                QMessageBox::information(nullptr, "下载完成", "文件已经下载到指定目录");
            }
        });
        request->accept();
    } else {
        request->cancel();
    }
}

void MainWindow::FindPageText_()
{
    auto text = QInputDialog::getText(nullptr, "查找页面内容", "关键字:", QLineEdit::Normal);
    if (topBrowserWindow_ != nullptr) {
        topBrowserWindow_->findText(text, QWebEnginePage::FindFlag::FindCaseSensitively);
    }
}

void MainWindow::PrintPageToPdf_()
{
    if (topBrowserWindow_ != nullptr) {
        auto documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
        auto downloadPath = documentsPath + "/" + topBrowserWindow_->title() + ".pdf";
        downloadPath = QFileDialog::getSaveFileName(nullptr, "保存至", downloadPath, ".pdf");
        topBrowserWindow_->printToPdf(downloadPath);
    }
}
