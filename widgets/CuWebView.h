#pragma once

#include "utils/qt_misc.h"
#include "objects/CuSchemeHandler.h"

class BookmarkProvider
{
    public:
        struct Bookmark
        {
            QString id;
            QString url;
            QString title;
        };

        static void AddBookmark(const QUrl &url, const QString &title)
        {
            auto &bookmarksJSON = GetInstance_()->bookmarksJSON_;
            CU::JSONArray bookmarksArray{};
            if (bookmarksJSON.contains("bookmarksList")) {
                bookmarksArray = bookmarksJSON.at("bookmarksList").toArray();
            }
            CU::JSONObject bookmark{};
            bookmark["id"] = std::to_string(GetTimeStampMsQt());
            bookmark["url"] = url.toString().toStdString();
            bookmark["title"] = title.toStdString();
            bookmarksArray.add(bookmark);
            bookmarksJSON["bookmarksList"] = bookmarksArray;
        }

        static void RemoveBookmark(const std::string &id)
        {
            auto &bookmarksJSON = GetInstance_()->bookmarksJSON_;
            if (!bookmarksJSON.contains("bookmarksList")) {
                return;
            }
            auto bookmarksArray = bookmarksJSON.at("bookmarksList").toArray();
            for (const auto &item : bookmarksArray) {
                if (item.toObject().at("id").toString() == id) {
                    bookmarksArray.remove(item);
                    break;
                }
            }
            bookmarksJSON["bookmarksList"] = bookmarksArray;
        }

        static std::vector<Bookmark> GetBookmarks()
        {
            auto &bookmarksJSON = GetInstance_()->bookmarksJSON_;
            if (!bookmarksJSON.contains("bookmarksList")) {
                return {};
            }
            std::vector<Bookmark> bookmarks{};
            auto bookmarksList = bookmarksJSON.at("bookmarksList").toArray().toListObject();
            for (const auto &bookmarkJSON : bookmarksList) {
                Bookmark bookmark{};
                bookmark.id = bookmarkJSON.at("id").toString().c_str();
                bookmark.url = bookmarkJSON.at("url").toString().c_str();
                bookmark.title = bookmarkJSON.at("title").toString().c_str();
                bookmarks.emplace_back(bookmark);
            }
            return bookmarks;
        }

        static void SaveToDisk()
        {
            QFile bookmarksFile(QCoreApplication::applicationDirPath() + "\\bookmarks.json");
            bookmarksFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
            bookmarksFile.write((GetInstance_()->bookmarksJSON_).toString().c_str());
            bookmarksFile.close();
        }

    private:
        static BookmarkProvider* GetInstance_()
        {
            static BookmarkProvider* instance = nullptr;
            if (instance == nullptr) {
                instance = new BookmarkProvider();
            }
            return instance;
        }

        BookmarkProvider() : bookmarksJSON_()
        {
            QFile bookmarksFile(QCoreApplication::applicationDirPath() + "\\bookmarks.json");
            if (bookmarksFile.exists()) {
                bookmarksFile.open(QIODevice::ReadOnly);
                bookmarksJSON_ = CU::JSONObject(bookmarksFile.readAll().toStdString());
                bookmarksFile.close();
            }
        }

        CU::JSONObject bookmarksJSON_;
};

class HistoryProvider
{
    public:
        struct HistoryItem
        {
            QString url;
            QString title;
            QString time;
        };

        static void AddHistoryItem(const QUrl &url, const QString &title)
        {
            auto &historyJSON = GetInstance_()->historyJSON_;
            CU::JSONArray itemsArray{};
            if (historyJSON.contains("items")) {
                itemsArray = historyJSON.at("items").toArray();
            }
            CU::JSONObject historyItem{};
            historyItem["url"] = url.toString().toStdString();
            historyItem["title"] = title.toStdString();
            historyItem["time"] = GetTimeText_();
            itemsArray.add(historyItem);
            historyJSON["items"] = itemsArray;
        }

        static void ClearHistory()
        {
            (GetInstance_()->historyJSON_).clear();
        }

        static std::vector<HistoryItem> GetHistoryItems()
        {
            auto &historyJSON = GetInstance_()->historyJSON_;
            if (!historyJSON.contains("items")) {
                return {};
            }
            std::vector<HistoryItem> historyItems{};
            auto itemsList = historyJSON.at("items").toArray().toListObject();
            for (auto iter = (itemsList.end() - 1); iter >= itemsList.begin(); iter--) {
                HistoryItem item{};
                item.url = iter->at("url").toString().c_str();
                item.title = iter->at("title").toString().c_str();
                item.time = iter->at("time").toString().c_str();
                historyItems.emplace_back(item);
            }
            return historyItems;
        }

        static void SaveToDisk()
        {
            QFile historyFile(QCoreApplication::applicationDirPath() + "\\history.json");
            historyFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
            historyFile.write((GetInstance_()->historyJSON_).toString().c_str());
            historyFile.close();
        }

    private:
        static HistoryProvider* GetInstance_()
        {
            static HistoryProvider* instance = nullptr;
            if (instance == nullptr) {
                instance = new HistoryProvider();
            }
            return instance;
        }

        static std::string GetTimeText_()
        {
            auto now = std::chrono::system_clock::now();
            auto nowTime = std::chrono::system_clock::to_time_t(now);
            auto localTime = std::localtime(std::addressof(nowTime));
            char buffer[16] = { 0 };
            snprintf(buffer, sizeof(buffer), "%02d-%02d %02d:%02d:%02d",
                     localTime->tm_mon + 1, localTime->tm_mday, localTime->tm_hour, localTime->tm_min, localTime->tm_sec);
            std::string timeText(buffer);
            return timeText;
        }

        HistoryProvider() : historyJSON_()
        {
            QFile historyFile(QCoreApplication::applicationDirPath() + "\\history.json");
            if (historyFile.exists()) {
                historyFile.open(QIODevice::ReadOnly);
                historyJSON_ = CU::JSONObject(historyFile.readAll().toStdString());
                historyFile.close();
            }
        }

        CU::JSONObject historyJSON_;
};

class CuWebView : public QWebEngineView
{
    Q_OBJECT
    public:
        static QWebEngineProfile* GetWebEngineProfile_();

        explicit CuWebView(QWidget* parent = nullptr);
        ~CuWebView();

    signals:
        void NewWindowCreated(CuWebView* newBrowserWindow);

    protected:
        CuWebView* createWindow(QWebEnginePage::WebWindowType type) override;
        void closeEvent(QCloseEvent* event) override;

    private:
        QWidget* parent_;
};
