#include "utils.h"

int GetCompileDateCode(const std::string &compileDate)
{
    int year = 0;
    int month = 0;
    int day = 0;

    char monthStr[4] = { 0 };
    sscanf(compileDate.c_str(), "%s %d %d", monthStr, &day, &year);
    if (strcmp(monthStr, "Jan") == 0) {
        month = 1;
    } else if (strcmp(monthStr, "Feb") == 0) {
        month = 2;
    } else if (strcmp(monthStr, "Mar") == 0) {
        month = 3;
    } else if (strcmp(monthStr, "Apr") == 0) {
        month = 4;
    } else if (strcmp(monthStr, "May") == 0) {
        month = 5;
    } else if (strcmp(monthStr, "Jun") == 0) {
        month = 6;
    } else if (strcmp(monthStr, "Jul") == 0) {
        month = 7;
    } else if (strcmp(monthStr, "Aug") == 0) {
        month = 8;
    } else if (strcmp(monthStr, "Sep") == 0) {
        month = 9;
    } else if (strcmp(monthStr, "Oct") == 0) {
        month = 10;
    } else if (strcmp(monthStr, "Nov") == 0) {
        month = 11;
    } else if (strcmp(monthStr, "Dec") == 0) {
        month = 12;
    }

    return year * 10000 + month * 100 + day;
}

std::vector<std::string> StrSplit(const std::string &str, const std::string &delimiter)
{
    std::vector<std::string> strList{};

    size_t start_pos = 0;
    size_t pos = str.find(delimiter);
    while (pos != std::string::npos) {
        strList.emplace_back(str.substr(start_pos, pos - start_pos));
        start_pos = pos + delimiter.size();
        pos = str.find(delimiter, start_pos);
    }
    if (start_pos < str.size()) {
        strList.emplace_back(str.substr(start_pos));
    }

    return strList;
}

std::string StrDivide(const std::string &str, const size_t &idx)
{
    std::string ret = "";

    size_t start_pos = 0;
    size_t space_num = 0;
    for (size_t pos = 1; pos < str.size(); pos++) {
        if (str[pos] == ' ' && str[pos - 1] != ' ') {
            if (space_num == idx) {
                ret = str.substr(start_pos, pos - start_pos);
            }
            space_num++;
        } else if (str[pos] != ' ' && str[pos - 1] == ' ') {
            start_pos = pos;
        }
    }

    return ret;
}

std::string StrMerge(const char* format, ...)
{
    std::string str = "";
    {
        va_list arg;
        va_start(arg, format);
        int size = vsnprintf(nullptr, 0, format, arg);
        va_end(arg);
        if (size > 0) {
            str.resize((size_t)size + 1);
            va_start(arg, format);
            vsnprintf(&str[0], str.size(), format, arg);
            va_end(arg);
        }
        str.resize(strlen(str.c_str()));
    }

    return str;
}

std::string GetPrevString(const std::string &str, const char &chr)
{
    std::string prevString = str;

    size_t pos = prevString.find(chr);
    if (pos != std::string::npos) {
        prevString = prevString.substr(0, pos);
    }

    return prevString;
}

std::string GetRePrevString(const std::string &str, const char &chr)
{
    std::string prevString = str;

    size_t pos = prevString.rfind(chr);
    if (pos != std::string::npos) {
        prevString = prevString.substr(0, pos);
    }

    return prevString;
}

std::string GetPostString(const std::string &str, const char &chr)
{
    std::string postString = str;

    size_t pos = postString.find(chr);
    if (pos != std::string::npos) {
        postString = postString.substr(pos + 1);
    }

    return postString;
}

std::string GetRePostString(const std::string &str, const char &chr)
{
    std::string postString = str;

    size_t pos = postString.rfind(chr);
    if (pos != std::string::npos) {
        postString = postString.substr(pos + 1);
    }

    return postString;
}

bool StrContains(const std::string &str, const std::string &subStr)
{
    bool contains = false;
    if (str.find(subStr) != std::string::npos) {
        contains = true;
    }

    return contains;
}

std::vector<QString> StrSplitQt(const QString &str, const QString &delimiter)
{
    std::vector<QString> strList{};

    int64_t start_pos = 0;
    int64_t pos = str.indexOf(delimiter);
    while (pos != -1) {
        strList.emplace_back(str.mid(start_pos, pos - start_pos));
        start_pos = pos + delimiter.size();
        pos = str.indexOf(delimiter, start_pos);
    }
    if (start_pos < str.size()) {
        strList.emplace_back(str.mid(start_pos));
    }

    return strList;
}

QString StrDivideQt(const QString &str, const int64_t &idx)
{
    QString ret = "";

    int64_t start_pos = 0;
    int64_t space_num = 0;
    for (int64_t pos = 1; pos < str.size(); pos++) {
        if (str[pos].isSpace() && !str[pos - 1].isSpace()) {
            if (space_num == idx) {
                ret = str.mid(start_pos, pos - start_pos);
            }
            space_num++;
        } else if (!str[pos].isSpace() && str[pos - 1].isSpace()) {
            start_pos = pos;
        }
    }

    return ret;
}

QString StrMergeQt(const char* format, ...)
{
    std::string str = "";
    {
        va_list arg;
        va_start(arg, format);
        int size = vsnprintf(nullptr, 0, format, arg);
        va_end(arg);
        if (size > 0) {
            str.resize((size_t)size + 1);
            va_start(arg, format);
            vsnprintf(&str[0], str.size(), format, arg);
            va_end(arg);
        }
        str.resize(strlen(str.c_str()));
    }

    return QString(str.c_str());
}

QString GetPrevStringQt(const QString &str, const QChar &chr)
{
    QString prevString = str;

    int64_t pos = prevString.indexOf(chr);
    if (pos != -1) {
        prevString = prevString.mid(0, pos);
    }

    return prevString;
}

QString GetRePrevStringQt(const QString &str, const QChar &chr)
{
    QString prevString = str;

    int64_t pos = prevString.lastIndexOf(chr);
    if (pos != -1) {
        prevString = prevString.mid(0, pos);
    }

    return prevString;
}

QString GetPostStringQt(const QString &str, const QChar &chr)
{
    QString postString = str;

    int64_t pos = postString.indexOf(chr);
    if (pos != -1) {
        postString = postString.mid(pos + 1);
    }

    return postString;
}

QString GetRePostStringQt(const QString &str, const QChar &chr)
{
    QString postString = str;

    int64_t pos = postString.lastIndexOf(chr);
    if (pos != -1) {
        postString = postString.mid(pos + 1);
    }

    return postString;
}

uint64_t GetTimeStampMs()
{
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
    uint64_t timestamp_ms = now_ms.time_since_epoch().count();

    return timestamp_ms;
}
