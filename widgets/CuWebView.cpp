#include "widgets/CuWebView.h"

CuWebView::CuWebView(QWidget* parent, QWebEngineProfile* profile) :
    QWebEngineView(parent),
    parent_(parent),
    profile_(profile)
{
    QWebEnginePage* page = new QWebEnginePage(profile_, this);
    connect(page, &QWebEnginePage::fullScreenRequested, this, [=](QWebEngineFullScreenRequest request){
        request.accept();
    });
    setPage(page);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

CuWebView::~CuWebView() { }

CuWebView* CuWebView::createWindow(QWebEnginePage::WebWindowType type)
{
    Q_UNUSED(type);
    CuWebView* newBrowserWindow = new CuWebView(parent_, profile_);
    emit NewWindowCreated(newBrowserWindow);

    return newBrowserWindow;
}

void CuWebView::closeEvent(QCloseEvent* event)
{
    event->accept();
}
