#include "windows/MainWindow.h"

constexpr char buttonStyle[] =
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
    "QPushButton::menu-indicator { width: 0; height: 0; }                        ";

constexpr char menuStyle[] =
    "QMenu::item {                                                               "
    "   padding: 5px;                                                            "
    "   background-color: #FFFFFF;                                               "
    "   font-size: 12px;                                                         "
    "   color: #000000;                                                          "
    "}                                                                           "
    "QMenu::item:selected {                                                      "
    "   background-color: #F0F0F0;                                               "
    "}                                                                           "
    "QMenu::item:pressed {                                                       "
    "   background-color: #E0E0E0;                                               "
    "}                                                                           ";

constexpr char editStyle[] =
    "QLineEdit {                                                                 "
    "   border: none;                                                            "
    "   background-color: #F0F0F0;                                               "
    "   color: #000000;                                                          "
    "   font-size: 14px;                                                         "
    "   border-radius: 5px;                                                      "
    "   padding-left: 5px;                                                       "
    "   padding-right: 5px;                                                      "
    "}                                                                           "
    "QLineEdit:hover {                                                           "
    "   background-color: #E8E8E8;                                               "
    "}                                                                           "
    "QLineEdit:pressed {                                                         "
    "   background-color: #E8E8E8;                                               "
    "}                                                                           ";


MainWindow::MainWindow(const QString &path) :
    QMainWindow(),
    logger_(CuLogger::GetLogger()),
    path_(path),
    browserProfile_(nullptr),
    baseWidget_(nullptr),
    baseLayout_(nullptr),
    controlBarLayout_(nullptr),
    urlEdit_(nullptr),
    loadButton_(nullptr),
    backButton_(nullptr),
    forwardButton_(nullptr),
    reflashButton_(nullptr),
    menuButton_(nullptr),
    browserTabLayout_(nullptr),
    addButton_(nullptr),
    buttonToWindow_(),
    windowToButton_(),
    topBrowserWindow_(nullptr),
    browserMenu_(nullptr)
{
    setAttribute(Qt::WA_DeleteOnClose, true);
    setFocusPolicy(Qt::ClickFocus);
    resize(1000, 600);
    setMinimumSize(800, 500);
    setWindowIcon(QIcon(":/res/media/cu_icon.ico"));
    setWindowTitle("CuprumBrowserQt");
    setStyleSheet("background-color: #FFFFFF;");
    {
        browserProfile_ = new QWebEngineProfile(QString::fromLatin1("CuprumBrowserQt.%1").arg(qWebEngineChromiumVersion()));
        browserProfile_->settings()->setAttribute(QWebEngineSettings::AutoLoadImages, true);
        browserProfile_->settings()->setAttribute(QWebEngineSettings::LocalStorageEnabled, true);
        browserProfile_->settings()->setAttribute(QWebEngineSettings::DnsPrefetchEnabled, true);
        browserProfile_->settings()->setAttribute(QWebEngineSettings::JavascriptEnabled, true);
        browserProfile_->settings()->setAttribute(QWebEngineSettings::JavascriptCanOpenWindows, true);
        browserProfile_->settings()->setAttribute(QWebEngineSettings::JavascriptCanAccessClipboard, true);
        browserProfile_->settings()->setAttribute(QWebEngineSettings::JavascriptCanPaste, true);
        browserProfile_->settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls, true);
        browserProfile_->settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessFileUrls, true);
        browserProfile_->settings()->setAttribute(QWebEngineSettings::XSSAuditingEnabled, true);
        browserProfile_->settings()->setAttribute(QWebEngineSettings::ScrollAnimatorEnabled, true);
        browserProfile_->settings()->setAttribute(QWebEngineSettings::WebGLEnabled, true);
        browserProfile_->settings()->setAttribute(QWebEngineSettings::Accelerated2dCanvasEnabled, true);
        browserProfile_->settings()->setAttribute(QWebEngineSettings::WebRTCPublicInterfacesOnly, true);
        browserProfile_->settings()->setAttribute(QWebEngineSettings::PluginsEnabled, false);
        browserProfile_->settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);
        browserProfile_->settings()->setAttribute(QWebEngineSettings::ScreenCaptureEnabled, false);
        browserProfile_->settings()->setAttribute(QWebEngineSettings::HyperlinkAuditingEnabled, false);
        browserProfile_->settings()->setAttribute(QWebEngineSettings::ErrorPageEnabled, true);
        browserProfile_->settings()->setAttribute(QWebEngineSettings::AllowRunningInsecureContent, false);
        browserProfile_->settings()->setAttribute(QWebEngineSettings::AllowGeolocationOnInsecureOrigins, false);
        browserProfile_->settings()->setAttribute(QWebEngineSettings::AllowWindowActivationFromJavaScript, false);
        browserProfile_->settings()->setAttribute(QWebEngineSettings::ShowScrollBars, true);
        browserProfile_->settings()->setAttribute(QWebEngineSettings::PlaybackRequiresUserGesture, false);
        browserProfile_->settings()->setAttribute(QWebEngineSettings::PdfViewerEnabled, true);
        browserProfile_->settings()->setAttribute(QWebEngineSettings::AutoLoadIconsForPage, true);
        QString browserUserAgent = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) "
                                   "Chrome/" + QString(qWebEngineChromiumVersion()) + " Safari/537.36";
        browserProfile_->setHttpUserAgent(browserUserAgent);
        browserProfile_->clearAllVisitedLinks();
        browserProfile_->clearHttpCache();
        browserProfile_->setCachePath(path_ + "\\browser_cache");
        browserProfile_->setPersistentStoragePath(path_ + "\\browser_storage");
        browserProfile_->setPersistentCookiesPolicy(QWebEngineProfile::AllowPersistentCookies);
        browserProfile_->setHttpCacheType(QWebEngineProfile::DiskHttpCache);
        browserProfile_->installUrlSchemeHandler("cu", new CuSchemeHandler(path_));
        QObject::connect(browserProfile_, &QWebEngineProfile::downloadRequested, this, &MainWindow::Browser_onDownloadRequested);
    }
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
        controlBarLayout_->setContentsMargins(2, 0, 2, 0);
        controlBarLayout_->setSpacing(2);
        baseLayout_->addLayout(controlBarLayout_);
    }
    {
        backButton_ = new QPushButton(baseWidget_);
        backButton_->setFixedSize(30, 30);
        backButton_->setIcon(QIcon(":/res/media/back.png"));
        backButton_->setStyleSheet(buttonStyle);
        backButton_->setContentsMargins(0, 0, 0, 0);
        backButton_->setToolTip("Go back.");
        QObject::connect(backButton_, &QPushButton::clicked, this, [=](){
            GoBack_();
        });
        controlBarLayout_->addWidget(backButton_);
    }
    {
        forwardButton_ = new QPushButton(baseWidget_);
        forwardButton_->setFixedSize(30, 30);
        forwardButton_->setIcon(QIcon(":/res/media/forward.png"));
        forwardButton_->setStyleSheet(buttonStyle);
        forwardButton_->setContentsMargins(0, 0, 0, 0);
        forwardButton_->setToolTip("Go forward.");
        QObject::connect(forwardButton_, &QPushButton::clicked, this, [=](){
            GoForward_();
        });
        controlBarLayout_->addWidget(forwardButton_);
    }
    {
        reflashButton_ = new QPushButton(baseWidget_);
        reflashButton_->setFixedSize(30, 30);
        reflashButton_->setIcon(QIcon(":/res/media/reflash.png"));
        reflashButton_->setStyleSheet(buttonStyle);
        reflashButton_->setContentsMargins(0, 0, 0, 0);
        reflashButton_->setToolTip("Reflash page.");
        QObject::connect(reflashButton_, &QPushButton::clicked, this, [=](){
            Reflash_();
        });
        controlBarLayout_->addWidget(reflashButton_);
    }
    {
        urlEdit_ = new QLineEdit(baseWidget_);
        urlEdit_->setMinimumHeight(30);
        urlEdit_->setMaximumHeight(30);
        urlEdit_->setStyleSheet(editStyle);
        urlEdit_->setContentsMargins(0, 0, 0, 0);
        urlEdit_->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        urlEdit_->setToolTip("Enter your url.");
        QObject::connect(urlEdit_, &QLineEdit::returnPressed, this, [=](){
            LoadUrl_(urlEdit_->text());
        });
        controlBarLayout_->addWidget(urlEdit_);
    }
    {
        menuButton_ = new QPushButton(baseWidget_);
        menuButton_->setFixedSize(30, 30);
        menuButton_->setIcon(QIcon(":/res/media/menu.png"));
        menuButton_->setStyleSheet(buttonStyle);
        menuButton_->setContentsMargins(0, 0, 0, 0);
        menuButton_->setToolTip("Browser menu.");
        controlBarLayout_->addWidget(menuButton_);
    }
    {
        browserTabLayout_ = new QHBoxLayout();
        browserTabLayout_->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        browserTabLayout_->setContentsMargins(2, 2, 2, 2);
        browserTabLayout_->setSpacing(2);
        baseLayout_->addLayout(browserTabLayout_);
    }
    {
        addButton_ = new QPushButton(baseWidget_);
        addButton_->setFixedSize(30, 30);
        addButton_->setIcon(QIcon(":/res/media/add.png"));
        addButton_->setStyleSheet(buttonStyle);
        addButton_->setContentsMargins(0, 0, 0, 0);
        addButton_->setToolTip("Browser menu.");
        QObject::connect(addButton_, &QPushButton::clicked, this, [=](){
            AddBrowserWindow_(new CuWebView(baseWidget_, browserProfile_));
            LoadUrl_("cu://home/");
        });
        browserTabLayout_->addWidget(addButton_);
    }
    {
        browserMenu_ = new QMenu(menuButton_);
        browserMenu_->setFixedWidth(200);
        browserMenu_->setStyleSheet(menuStyle);
        {
            QAction* addTap = new QAction(browserMenu_);
            addTap->setShortcuts(QKeySequence::AddTab);
            addTap->setText("添加标签页");
            QObject::connect(addTap, &QAction::triggered, this, [=](){
                AddBrowserWindow_(new CuWebView(baseWidget_, browserProfile_));
                LoadUrl_("cu://home/");
            });
            browserMenu_->addAction(addTap);
        }
        {
            QAction* removeTab = new QAction(browserMenu_);
            removeTab->setShortcuts(QKeySequence::Close);
            removeTab->setText("关闭当前标签页");
            QObject::connect(removeTab, &QAction::triggered, this, [=](){
                RemoveBrowserWindow_(windowToButton_.at(topBrowserWindow_));
            });
            browserMenu_->addAction(removeTab);
        }
        browserMenu_->addSeparator();
        {
            QAction* openHomePage = new QAction(browserMenu_);
            openHomePage->setShortcuts(QKeySequence::Open);
            openHomePage->setText("打开首页");
            QObject::connect(openHomePage, &QAction::triggered, this, [=](){
                LoadUrl_("cu://home/");
            });
            browserMenu_->addAction(openHomePage);
        }
        {
            QAction* openBookmark = new QAction(browserMenu_);
            openBookmark->setShortcuts(QKeySequence::Bold);
            openBookmark->setText("打开书签页");
            QObject::connect(openBookmark, &QAction::triggered, this, [=](){
                LoadUrl_("cu://bookmarks/");
            });
            browserMenu_->addAction(openBookmark);
        }
        browserMenu_->addSeparator();
        {
            QAction* addBookmark = new QAction(browserMenu_);
            addBookmark->setShortcuts(QKeySequence::New);
            addBookmark->setText("将此页加入书签");
            QObject::connect(addBookmark, &QAction::triggered, this, [=](){
                AddBookmark_();
            });
            browserMenu_->addAction(addBookmark);
        }
        {
            QAction* zoomIn = new QAction(browserMenu_);
            zoomIn->setShortcuts(QKeySequence::ZoomIn);
            zoomIn->setText("放大当前页面");
            QObject::connect(zoomIn, &QAction::triggered, this, [=](){
                SetPageZoomIn_();
            });
            browserMenu_->addAction(zoomIn);
        }
        {
            QAction* zoomOut = new QAction(browserMenu_);
            zoomOut->setShortcuts(QKeySequence::ZoomOut);
            zoomOut->setText("缩小当前页面");
            QObject::connect(zoomOut, &QAction::triggered, this, [=](){
                SetPageZoomOut_();
            });
            browserMenu_->addAction(zoomOut);
        }
        {
            QAction* resetZoom = new QAction(browserMenu_);
            resetZoom->setShortcut(QKeySequence("Ctrl+R"));
            resetZoom->setText("还原当前页面缩放");
            QObject::connect(resetZoom, &QAction::triggered, this, [=](){
                ResetPageZoom_();
            });
            browserMenu_->addAction(resetZoom);
        }
        {
            QAction* openDevTool = new QAction(browserMenu_);
            openDevTool->setShortcut(QKeySequence("F12"));
            openDevTool->setText("打开开发人员工具");
            QObject::connect(openDevTool, &QAction::triggered, this, [=](){
                OpenDevTool_();
            });
            browserMenu_->addAction(openDevTool);
        }
        browserMenu_->addSeparator();
        {
            QAction* aboutBrowser = new QAction(browserMenu_);
            aboutBrowser->setText("关于浏览器");
            QObject::connect(aboutBrowser, &QAction::triggered, this, [=]() {
                LoadUrl_("cu://about/");
            });
            browserMenu_->addAction(aboutBrowser);
        }
        {
            QAction* quitBrowser = new QAction(browserMenu_);
            quitBrowser->setShortcut(QKeySequence("Alt+Esc"));
            quitBrowser->setText("退出");
            QObject::connect(quitBrowser, &QAction::triggered, this, [=](){
                close();
            });
            browserMenu_->addAction(quitBrowser);
        }
        menuButton_->setMenu(browserMenu_);
    }
    {
        AddBrowserWindow_(new CuWebView(baseWidget_, browserProfile_));
        LoadUrl_("cu://home/");
    }
    logger_->Info("MainWindow created.");
}

MainWindow::~MainWindow() { }

void MainWindow::resizeEvent(QResizeEvent* event)
{
    Q_UNUSED(event);
    if (urlEdit_ != nullptr) {
        urlEdit_->setCursorPosition(0);
    }
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    QDir(path_ + "\\browser_cache").removeRecursively();
    logger_->Info("MainWindow closed.");
    event->accept();
    deleteLater();
}

void MainWindow::AddBrowserWindow_(CuWebView* newBrowserWindow)
{
    if (topBrowserWindow_ != nullptr) {
        {
            QObject::disconnect(topBrowserWindow_, &CuWebView::urlChanged, this, &MainWindow::Browser_onUrlChanged);
            QObject::disconnect(topBrowserWindow_, &CuWebView::titleChanged, this, &MainWindow::Browser_onTitleChanged);
            QObject::disconnect(topBrowserWindow_, &CuWebView::iconChanged, this, &MainWindow::Browser_onIconChanged);
            QObject::disconnect(topBrowserWindow_, &CuWebView::NewWindowCreated, this, &MainWindow::Browser_onNewWindowCreated);
            topBrowserWindow_->setEnabled(false);
            topBrowserWindow_->setVisible(false);
        }
        {
            const auto &topWindowTabButton = windowToButton_.at(topBrowserWindow_);
            topWindowTabButton->SetFocused(false);
        }
    }
    {
        topBrowserWindow_ = newBrowserWindow;
        const auto &newTabButton = new CuTabButton(baseWidget_);
        buttonToWindow_[newTabButton] = newBrowserWindow;
        windowToButton_[newBrowserWindow] = newTabButton;
        {
            QObject::connect(newBrowserWindow, &CuWebView::urlChanged, this, &MainWindow::Browser_onUrlChanged);
            QObject::connect(newBrowserWindow, &CuWebView::titleChanged, this, &MainWindow::Browser_onTitleChanged);
            QObject::connect(newBrowserWindow, &CuWebView::iconChanged, this, &MainWindow::Browser_onIconChanged);
            QObject::connect(newBrowserWindow, &CuWebView::NewWindowCreated, this, &MainWindow::Browser_onNewWindowCreated);
            baseLayout_->addWidget(newBrowserWindow);
        }
        {
            newTabButton->SetFocused(true);
            newTabButton->setIcon(newBrowserWindow->icon());
            newTabButton->setText(newBrowserWindow->title());
            QObject::connect(newTabButton, &CuTabButton::MouseLeftButtonClicked, this, &MainWindow::ChangeTopWindow_);
            QObject::connect(newTabButton, &CuTabButton::MouseRightButtonClicked, this, &MainWindow::RemoveBrowserWindow_);
            browserTabLayout_->removeWidget(addButton_);
            browserTabLayout_->addWidget(newTabButton);
            browserTabLayout_->addWidget(addButton_);
        }
    }
}

void MainWindow::ChangeTopWindow_(CuTabButton* tabButton)
{
    const auto &newTopWindow = buttonToWindow_.at(tabButton);
    if (topBrowserWindow_ != nullptr) {
        {
            QObject::disconnect(topBrowserWindow_, &CuWebView::urlChanged, this, &MainWindow::Browser_onUrlChanged);
            QObject::disconnect(topBrowserWindow_, &CuWebView::titleChanged, this, &MainWindow::Browser_onTitleChanged);
            QObject::disconnect(topBrowserWindow_, &CuWebView::iconChanged, this, &MainWindow::Browser_onIconChanged);
            QObject::disconnect(topBrowserWindow_, &CuWebView::NewWindowCreated, this, &MainWindow::Browser_onNewWindowCreated);
            topBrowserWindow_->setEnabled(false);
            topBrowserWindow_->setVisible(false);
        }
        {
            const auto &topWindowTabButton = windowToButton_.at(topBrowserWindow_);
            topWindowTabButton->SetFocused(false);
        }
    }
    {
        topBrowserWindow_ = newTopWindow;
        {
            QObject::connect(newTopWindow, &CuWebView::urlChanged, this, &MainWindow::Browser_onUrlChanged);
            QObject::connect(newTopWindow, &CuWebView::titleChanged, this, &MainWindow::Browser_onTitleChanged);
            QObject::connect(newTopWindow, &CuWebView::iconChanged, this, &MainWindow::Browser_onIconChanged);
            QObject::connect(newTopWindow, &CuWebView::NewWindowCreated, this, &MainWindow::Browser_onNewWindowCreated);
            newTopWindow->setEnabled(true);
            newTopWindow->setVisible(true);
        }
        {
            const auto &tabButton = windowToButton_.at(newTopWindow);
            tabButton->SetFocused(true);
        }
    }
    {
        this->setWindowTitle("CuprumBrowserQt - " + newTopWindow->title());
        urlEdit_->setText(newTopWindow->url().toString());
        urlEdit_->setCursorPosition(0);
        tabButton->setIcon(newTopWindow->icon());
        tabButton->setText(newTopWindow->title());
    }
}

void MainWindow::RemoveBrowserWindow_(CuTabButton* tabButton)
{
    const auto &removeWindow = buttonToWindow_.at(tabButton);
    if (windowToButton_.size() == 1) {
        removeWindow->load(QUrl("cu://home/"));
        return;
    }
    if (removeWindow == topBrowserWindow_) {
        for (const auto &[button, window] : buttonToWindow_) {
            if (button != tabButton) {
                ChangeTopWindow_(button);
            }
        }
    }
    {
        baseLayout_->removeWidget(removeWindow);
        QObject::disconnect(removeWindow, &CuWebView::urlChanged, this, &MainWindow::Browser_onUrlChanged);
        QObject::disconnect(removeWindow, &CuWebView::titleChanged, this, &MainWindow::Browser_onTitleChanged);
        QObject::disconnect(removeWindow, &CuWebView::iconChanged, this, &MainWindow::Browser_onIconChanged);
        QObject::disconnect(removeWindow, &CuWebView::NewWindowCreated, this, &MainWindow::Browser_onNewWindowCreated);
        removeWindow->close();
        removeWindow->deleteLater();
    }
    {
        browserTabLayout_->removeWidget(tabButton);
        QObject::disconnect(tabButton, &CuTabButton::MouseLeftButtonClicked, this, &MainWindow::ChangeTopWindow_);
        QObject::disconnect(tabButton, &CuTabButton::MouseRightButtonClicked, this, &MainWindow::RemoveBrowserWindow_);
        tabButton->deleteLater();
    }
    buttonToWindow_.erase(tabButton);
    windowToButton_.erase(removeWindow);
}

void MainWindow::LoadUrl_(const QString &url)
{
    if (topBrowserWindow_ != nullptr) {
        QString currentUrl = url;
        if (!currentUrl.contains("http://") && !currentUrl.contains("https://") && 
            !currentUrl.contains("cu://") && !currentUrl.contains("file:///")) {
            currentUrl = "http://" + currentUrl;
        }
        topBrowserWindow_->load(QUrl(currentUrl));
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

void MainWindow::Reflash_()
{
    if (topBrowserWindow_ != nullptr) {
        topBrowserWindow_->reload();
    }
}

void MainWindow::SetPageZoomIn_()
{
    if (topBrowserWindow_ != nullptr) {
        const auto &zoomFactor = topBrowserWindow_->zoomFactor();
        if (zoomFactor < 2.0) {
            topBrowserWindow_->setZoomFactor(zoomFactor + 0.1);
        }
    }
}

void MainWindow::SetPageZoomOut_()
{
    if (topBrowserWindow_ != nullptr) {
        const auto &zoomFactor = topBrowserWindow_->zoomFactor();
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
        CuWebView* devToolView = new CuWebView(this, browserProfile_);
        topBrowserWindow_->page()->triggerAction(QWebEnginePage::InspectElement);
        topBrowserWindow_->page()->setDevToolsPage(devToolView->page());
        AddBrowserWindow_(devToolView);
    }
}

void MainWindow::AddBookmark_()
{
    if (topBrowserWindow_ != nullptr) {
        JsonObject bookmarksJson{};
        {
            QFile bookmarksFile = QFile(path_ + "\\bookmarks.json");
            if (bookmarksFile.exists()) {
                bookmarksFile.open(QIODevice::ReadOnly);
                bookmarksJson = JsonObject(bookmarksFile.readAll().toStdString());
            }
            bookmarksFile.close();
        }
        std::vector<JsonObject> bookmarksList{};
        if (bookmarksJson.Contains("bookmarksList")) {
            bookmarksList = bookmarksJson.GetArrayJson("bookmarksList");
        }
        {
            JsonObject bookmark{};
            bookmark.PutValueString("id", std::to_string(GetTimeStampMs()));
            bookmark.PutValueString("title", topBrowserWindow_->title().toStdString());
            bookmark.PutValueString("url", topBrowserWindow_->url().toString().toStdString());
            bookmarksList.emplace_back(bookmark);
        }
        bookmarksJson.PutArrayJson("bookmarksList", bookmarksList);
        {
            QFile bookmarksFile = QFile(path_ + "\\bookmarks.json");
            bookmarksFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
            bookmarksFile.write(bookmarksJson.PrintToString(false).c_str());
            bookmarksFile.close();
        }
    }
}

void MainWindow::Browser_onUrlChanged(const QUrl &url)
{
    urlEdit_->setText(url.toString());
    urlEdit_->setCursorPosition(0);
}

void MainWindow::Browser_onTitleChanged(const QString &title)
{
    this->setWindowTitle("CuprumBrowserQt - " + title);
    if (topBrowserWindow_ != nullptr) {
        windowToButton_.at(topBrowserWindow_)->setText(title);
    }
}

void MainWindow::Browser_onIconChanged(const QIcon &icon)
{
    if (topBrowserWindow_ != nullptr) {
        windowToButton_.at(topBrowserWindow_)->setIcon(icon);
    }
}

void MainWindow::Browser_onNewWindowCreated(CuWebView* newBrowserWindow)
{
    if (windowToButton_.count(newBrowserWindow) == 0) {
        AddBrowserWindow_(newBrowserWindow);
    }
}

void MainWindow::Browser_onDownloadRequested(QWebEngineDownloadRequest* request)
{
    if (QMessageBox::question(this, "获取到下载请求", "确定要下载 " + request->suggestedFileName() + " 文件吗?",
        QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        QString downloadPath = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
        downloadPath = QFileDialog::getExistingDirectory(this, "选择下载目录", downloadPath, QFileDialog::ShowDirsOnly);
        request->setDownloadDirectory(downloadPath);
        QProgressDialog* downloadProgressDialog = new QProgressDialog("文件下载中", "取消", 0, request->totalBytes(), this);
        downloadProgressDialog->setWindowModality(Qt::NonModal);
        downloadProgressDialog->setAutoClose(true);
        downloadProgressDialog->setAutoReset(false);
        downloadProgressDialog->setValue(0);
        downloadProgressDialog->setFixedSize(300, 120);
        downloadProgressDialog->show();
        QObject::connect(request, &QWebEngineDownloadRequest::receivedBytesChanged, this, [=](){
            downloadProgressDialog->setValue(request->receivedBytes());
            if (downloadProgressDialog->wasCanceled()) {
                request->cancel();
                downloadProgressDialog->close();
                downloadProgressDialog->deleteLater();
            }
        });
        QObject::connect(request, &QWebEngineDownloadRequest::isFinishedChanged, this, [=](){
            if (request->state() == QWebEngineDownloadRequest::DownloadCompleted) {
                downloadProgressDialog->close();
                downloadProgressDialog->deleteLater();
                QMessageBox::information(this, "下载完成", "文件已经下载到: " + downloadPath);
            }
        });
        request->accept();
    } else {
        request->cancel();
    }
}
