#pragma once

#include "qt_misc.h"
#include "CuJSONObject.h"

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
            const auto &bookmarksJSON = GetInstance_()->bookmarksJSON_;
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
            const auto &bookmarksJSON = GetInstance_()->bookmarksJSON_;
            QFile bookmarksFile(QApplication::applicationDirPath() + "\\bookmarks.json");
            bookmarksFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
            bookmarksFile.write(bookmarksJSON.toString().data());
            bookmarksFile.flush();
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
            QFile bookmarksFile(QApplication::applicationDirPath() + "\\bookmarks.json");
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
            CU::JSONObject itemJSON{};
            itemJSON["url"] = url.toString().toStdString();
            itemJSON["title"] = title.toStdString();
            itemJSON["time"] = GetTimeText_();
            {
                auto &historyJSON = GetInstance_()->historyJSON_;
                auto key = itemJSON.at("url").toString();
                if (historyJSON.contains(key)) {
                    historyJSON.remove(key);
                }
                historyJSON.add(key, itemJSON);
            }
        }

        static void ClearHistory()
        {
            auto &historyJSON = GetInstance_()->historyJSON_;
            historyJSON.clear();
        }

        static std::vector<HistoryItem> GetHistoryItems()
        {
            const auto &historyJSON = GetInstance_()->historyJSON_;
            if (historyJSON.size() == 0) {
                return {};
            }
            std::vector<HistoryItem> items{};
            auto pairs = historyJSON.toPairs();
            for (auto iter = (pairs.end() - 1); iter >= pairs.begin(); iter--) {
                auto itemJSON = (iter->value).toObject();
                if (itemJSON.contains("url") && itemJSON.at("url") == iter->key) {
                    HistoryItem item{};
                    item.url = itemJSON.at("url").toString().c_str();
                    item.title = itemJSON.at("title").toString().c_str();
                    item.time = itemJSON.at("time").toString().c_str();
                    items.emplace_back(item);
                }
            }
            return items;
        }

        static void SaveToDisk()
        {
            const auto &historyJSON = GetInstance_()->historyJSON_;
            QFile historyFile(QApplication::applicationDirPath() + "\\history.json");
            historyFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
            historyFile.write(historyJSON.toString().data());
            historyFile.flush();
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
            QFile historyFile(QApplication::applicationDirPath() + "\\history.json");
            if (historyFile.exists()) {
                historyFile.open(QIODevice::ReadOnly);
                historyJSON_ = CU::JSONObject(historyFile.readAll().toStdString());
                historyFile.close();
            }
        }

        CU::JSONObject historyJSON_;
};
