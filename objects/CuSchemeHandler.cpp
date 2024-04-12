#include "CuSchemeHandler.h"

constexpr char bookmarkTemplate[] =
    "<div class=\"bookmark-item-container\">                                                                         "
    "   <p class=\"item-name\" onclick=\"window.location.href=\'{{ BOOKMARK_URL }}\'\">{{ BOOKMARK_TITLE }}</p>      "
    "   <button class=\"item-delete-button\" onclick=\"window.location.href=\'{{ DELETE_URL }}\'; return false;\">   "
    "       <span>删除</span>                                                                                         "
    "   </button>                                                                                                    "
    "</div>                                                                                                          ";

constexpr char historyItemTemplate[] =
    "<div class=\"history-item-container\">                                                                          "
    "   <p class=\"item-name\" onclick=\"window.location.href=\'{{ HISTORY_URL }}\'\">{{ HISTORY_TITLE }}</p>        "
    "   <p class=\"item-time\">{{ HISTORY_TIME }}</p>                                                                "
    "</div>                                                                                                          ";

CuSchemeHandler::CuSchemeHandler(QObject* parent) : QWebEngineUrlSchemeHandler(parent) { }

CuSchemeHandler::~CuSchemeHandler() { }

void CuSchemeHandler::requestStarted(QWebEngineUrlRequestJob *job)
{
    auto requestUrl = job->requestUrl().toString().toStdString();
    if (requestUrl == "cu://home/") {
        job->reply("text/html", new QFile(":/res/html/homepage.html", job));
    } else if (requestUrl == "cu://image/background.jpg") {
        job->reply("image/jpg", new QFile(":/res/media/background.jpg", job));
    } else if (requestUrl == "cu://image/cu_icon.png") {
        job->reply("image/png", new QFile(":/res/media/cu_icon.png", job));
    } else if (requestUrl == "cu://about/") {
        auto webPageFile = new QBuffer(job);
        webPageFile->setData(GetAboutHtml_().toUtf8());
        job->reply("text/html", webPageFile);
    } else if (requestUrl == "cu://bookmarks/") {
        auto webPageFile = new QBuffer(job);
        webPageFile->setData(GetBookmarkHtml_().toUtf8());
        job->reply("text/html", webPageFile);
    } else if (requestUrl == "cu://history/") {
        auto webPageFile = new QBuffer(job);
        webPageFile->setData(GetHistoryHtml_().toUtf8());
        job->reply("text/html", webPageFile);
    } else if (StrContains(requestUrl, "cu://bookmarks/delete=")) {
        BookmarkProvider::RemoveBookmark(GetRePostString(requestUrl, "="));
        job->redirect(QUrl("cu://bookmarks/"));
    } else if (requestUrl == "cu://history/clear") {
        HistoryProvider::ClearHistory();
        job->redirect(QUrl("cu://history/"));
    } else {
        job->fail(QWebEngineUrlRequestJob::UrlInvalid);
    }
}

QString CuSchemeHandler::GetBookmarkHtml_()
{
    QString htmlText{};
    {
        QFile templateHtml(":/res/html/template_bookmarks.html");
        templateHtml.open(QIODevice::ReadOnly);
        htmlText = templateHtml.readAll();
        templateHtml.close();
    }
    {
        QString bookmarksData{};
        auto bookmarks = BookmarkProvider::GetBookmarks();
        if (bookmarks.size() > 0) {
            for (const auto &bookmark : bookmarks) {
                auto deleteUrl = QString("cu://bookmarks/delete=") + bookmark.id;
                auto bookmarkText = QString(bookmarkTemplate)
                                        .replace("{{ BOOKMARK_TITLE }}", bookmark.title)
                                        .replace("{{ BOOKMARK_URL }}", bookmark.url)
                                        .replace("{{ DELETE_URL }}", deleteUrl);
                bookmarksData += bookmarkText;
            }
        } else {
            bookmarksData = "<br/><p>本来无一物, 何处惹尘埃.</p>";
        }
        htmlText.replace("{% BOOKMARKS_DATA %}", bookmarksData);
    }
    return htmlText;
}

QString CuSchemeHandler::GetAboutHtml_()
{
    QString htmlText{};
    {
        QFile templateHtml(":/res/html/aboutpage.html");
        templateHtml.open(QIODevice::ReadOnly);
        htmlText = templateHtml.readAll();
        templateHtml.close();
    }
    {
        QString browserVersion(StrMerge("V1 (%d)", GetCompileDateCode()).c_str());
        QString chromiumVersion(qWebEngineChromiumVersion());
        htmlText = htmlText.replace("{{ BROWSER_VER }}", browserVersion).replace("{{ CHROMIUM_VER }}", chromiumVersion);
    }
    return htmlText;
}

QString CuSchemeHandler::GetHistoryHtml_()
{
    QString htmlText{};
    {
        QFile templateHtml(":/res/html/template_history.html");
        templateHtml.open(QIODevice::ReadOnly);
        htmlText = templateHtml.readAll();
        templateHtml.close();
    }
    {
        QString historyData{};
        auto historyItems = HistoryProvider::GetHistoryItems();
        if (historyItems.size() > 0) {
            for (const auto &item : historyItems) {
                historyData += QString(historyItemTemplate)
                                   .replace("{{ HISTORY_URL }}", item.url)
                                   .replace("{{ HISTORY_TITLE }}", item.title)
                                   .replace("{{ HISTORY_TIME }}", item.time);
            }
        } else {
            historyData = "<br/><p>本来无一物, 何处惹尘埃.</p>";
        }
        htmlText = htmlText.replace("{% HISTORY_DATA %}", historyData);
    }
    return htmlText;
}
