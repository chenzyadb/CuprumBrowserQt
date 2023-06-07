#include "objects/CuSchemeHandler.h"

constexpr char bookmarkTemplate[] =
    "<div class=\"bookmark-item-container\">                                                                      "
    "   <p class=\"item-name\" onclick=\"window.location.href='{{ BOOKMARK_URL }}'\">{{ BOOKMARK_TITLE }}</p>     "
    "   <button class=\"item-delete-button\" onclick=\"window.location.href='{{ DELETE_URL }}'; return false;\">  "
    "       <span>删除</span>                                                                                      "
    "   </button>                                                                                                 "
    "</div>                                                                                                       ";

CuSchemeHandler::CuSchemeHandler(const QString &path) : QWebEngineUrlSchemeHandler(), path_(path) { }

CuSchemeHandler::~CuSchemeHandler() { }

void CuSchemeHandler::requestStarted(QWebEngineUrlRequestJob *job)
{
    const auto &requestUrl = job->requestUrl().toString();
    if (requestUrl == "cu://home/") {
        job->reply("text/html", new QFile(":/res/html/homepage.html"));
    } else if (requestUrl == "cu://about/") {
        job->reply("text/html", new QFile(":/res/html/aboutpage.html"));
    } else if (requestUrl == "cu://image/background.jpg") {
        job->reply("image/jpg", new QFile(":/res/media/background.jpg"));
    } else if (requestUrl == "cu://image/cu_icon.png") {
        job->reply("image/png", new QFile(":/res/media/cu_icon.png"));
    } else if (requestUrl == "cu://bookmarks/") {
        QString htmlText = GetBookmarkHtml_();
        job->reply("text/html", new QBuffer(new QByteArray(htmlText.toUtf8()), job));
    } else if (requestUrl.contains("cu://bookmarks/delete=")) {
        QString deleteBookmarkId = GetRePostStringQt(requestUrl, '=');
        DeleteBookmark_(deleteBookmarkId);
        job->redirect(QUrl("cu://bookmarks/"));
    } else {
        job->fail(QWebEngineUrlRequestJob::UrlInvalid);
    }
}

QString CuSchemeHandler::GetBookmarkHtml_()
{
    QString htmlText = "";
    {
        QFile templateHtml = QFile(":/res/html/template_bookmarks.html");
        templateHtml.open(QIODevice::ReadOnly);
        htmlText = templateHtml.readAll();
        templateHtml.close();
    }
    {
        JsonObject bookmarksJson{};
        {
            QFile bookmarksFile = QFile(path_ + "\\bookmarks.json");
            if (bookmarksFile.exists()) {
                bookmarksFile.open(QIODevice::ReadOnly);
                bookmarksJson = JsonObject(bookmarksFile.readAll().toStdString());
                bookmarksFile.close();
            }
        }
        QString bookmarksData = "";
        if (bookmarksJson.Contains("bookmarksList")) {
            const auto &bookmarksList = bookmarksJson.GetArrayJson("bookmarksList");
            for (const auto &bookmark : bookmarksList) {
                const QString &id = bookmark.GetValueString("id").c_str();
                const QString &title = bookmark.GetValueString("title").c_str();
                const QString &url = bookmark.GetValueString("url").c_str();
                const QString &bookmarkText = QString(bookmarkTemplate)
                                                  .replace("{{ BOOKMARK_TITLE }}", title)
                                                  .replace("{{ BOOKMARK_URL }}", url)
                                                  .replace("{{ DELETE_URL }}", "cu://bookmarks/delete=" + id);
                bookmarksData += bookmarkText;
            }
        }
        htmlText.replace("{% BOOKMARKS_DATA %}", bookmarksData);
    }

    return htmlText;
}

void CuSchemeHandler::DeleteBookmark_(const QString &id)
{
    JsonObject bookmarksJson{};
    {
        QFile bookmarksFile = QFile(path_ + "\\bookmarks.json");
        if (!bookmarksFile.exists()) {
            return;
        }
        bookmarksFile.open(QIODevice::ReadOnly);
        bookmarksJson = JsonObject(bookmarksFile.readAll().toStdString());
        bookmarksFile.close();
    }
    auto bookmarksList = bookmarksJson.GetArrayJson("bookmarksList");
    for (const auto &bookmark : bookmarksList) {
        if (bookmark.GetValueString("id") == id.toStdString()) {
            const auto &iter = std::find(bookmarksList.begin(), bookmarksList.end(), bookmark);
            bookmarksList.erase(iter);
            break;
        }
    }
    bookmarksJson.PutArrayJson("bookmarksList", bookmarksList);
    {
        QFile bookmarksFile = QFile(path_ + "\\bookmarks.json");
        bookmarksFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
        bookmarksFile.write(bookmarksJson.PrintToString(false).c_str());
        bookmarksFile.close();
    }
}
