#include "CuWebView.h"

constexpr char userAgent[] = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/[CHROME_VER] Safari/537.36";

QWebEngineProfile* CuWebView::GetWebEngineProfile_()
{
    static QWebEngineProfile* profile = nullptr;
    if (profile == nullptr) {
        auto browserUserAgent = QString(userAgent).replace("[CHROME_VER]", qWebEngineChromiumVersion());
        profile = new QWebEngineProfile("CuprumBrowserQt");
        profile->setPersistentStoragePath(QCoreApplication::applicationDirPath() + "\\browser_storage");
        profile->setDownloadPath(QStandardPaths::writableLocation(QStandardPaths::DownloadLocation));
        profile->setPersistentCookiesPolicy(QWebEngineProfile::AllowPersistentCookies);
        profile->setHttpCacheType(QWebEngineProfile::MemoryHttpCache);
        profile->setHttpUserAgent(browserUserAgent);
        profile->installUrlSchemeHandler("cu", new CuSchemeHandler(profile));
        auto settings = profile->settings();
        settings->setAttribute(QWebEngineSettings::AutoLoadImages, true);
        settings->setAttribute(QWebEngineSettings::JavascriptEnabled, true);
        settings->setAttribute(QWebEngineSettings::JavascriptCanOpenWindows, true);
        settings->setAttribute(QWebEngineSettings::JavascriptCanAccessClipboard, true);
        settings->setAttribute(QWebEngineSettings::LinksIncludedInFocusChain, true);
        settings->setAttribute(QWebEngineSettings::LocalStorageEnabled, true);
        settings->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls, true);
        settings->setAttribute(QWebEngineSettings::XSSAuditingEnabled, true);
        settings->setAttribute(QWebEngineSettings::SpatialNavigationEnabled, true);
        settings->setAttribute(QWebEngineSettings::LocalContentCanAccessFileUrls, true);
        settings->setAttribute(QWebEngineSettings::HyperlinkAuditingEnabled, true);
        settings->setAttribute(QWebEngineSettings::ScrollAnimatorEnabled, true);
        settings->setAttribute(QWebEngineSettings::ErrorPageEnabled, true);
        settings->setAttribute(QWebEngineSettings::PluginsEnabled, false);
        settings->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);
        settings->setAttribute(QWebEngineSettings::ScreenCaptureEnabled, true);
        settings->setAttribute(QWebEngineSettings::WebGLEnabled, false);
        settings->setAttribute(QWebEngineSettings::Accelerated2dCanvasEnabled, true);
        settings->setAttribute(QWebEngineSettings::AutoLoadIconsForPage, true);
        settings->setAttribute(QWebEngineSettings::TouchIconsEnabled, true);
        settings->setAttribute(QWebEngineSettings::FocusOnNavigationEnabled, true);
        settings->setAttribute(QWebEngineSettings::PrintElementBackgrounds, true);
        settings->setAttribute(QWebEngineSettings::AllowRunningInsecureContent, false);
        settings->setAttribute(QWebEngineSettings::AllowGeolocationOnInsecureOrigins, false);
        settings->setAttribute(QWebEngineSettings::AllowWindowActivationFromJavaScript, false);
        settings->setAttribute(QWebEngineSettings::ShowScrollBars, true);
        settings->setAttribute(QWebEngineSettings::PlaybackRequiresUserGesture, false);
        settings->setAttribute(QWebEngineSettings::WebRTCPublicInterfacesOnly, true);
        settings->setAttribute(QWebEngineSettings::JavascriptCanPaste, true);
        settings->setAttribute(QWebEngineSettings::DnsPrefetchEnabled, true);
        settings->setAttribute(QWebEngineSettings::PdfViewerEnabled, true);
        settings->setAttribute(QWebEngineSettings::NavigateOnDropEnabled, true);
        settings->setDefaultTextEncoding("utf-8");
    }
    return profile;
}

CuWebView::CuWebView(QWidget* parent) : QWebEngineView(GetWebEngineProfile_(), parent)
{
    auto page = this->page();
    connect(page, &QWebEnginePage::fullScreenRequested, this, [](QWebEngineFullScreenRequest request) {
        request.accept();
    });
    connect(page, &QWebEnginePage::loadFinished, this, [this]() {
        HistoryProvider::AddHistoryItem(url(), title());
    });
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

CuWebView::~CuWebView() { }

CuWebView* CuWebView::createWindow(QWebEnginePage::WebWindowType type)
{
    Q_UNUSED(type);
    auto newBrowserWindow = new CuWebView(parentWidget());
    emit NewWindowCreated(newBrowserWindow);
    return newBrowserWindow;
}

void CuWebView::closeEvent(QCloseEvent* event)
{
    event->accept();
}
