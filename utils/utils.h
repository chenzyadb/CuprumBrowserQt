#pragma once

#ifdef _MSC_VER
#pragma warning(disable : 4996)
#endif

#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <vector>

#include <QString>
#include <QChar>
#include <QFile>
#include <QDir>

int GetCompileDateCode(const std::string &compileDate);
std::vector<std::string> StrSplit(const std::string &str, const std::string &delimiter);
std::string StrDivide(const std::string &str, const size_t &idx);
std::string StrMerge(const char* format, ...);
std::string GetPrevString(const std::string &str, const char &chr);
std::string GetRePrevString(const std::string &str, const char &chr);
std::string GetPostString(const std::string &str, const char &chr);
std::string GetRePostString(const std::string &str, const char &chr);
bool StrContains(const std::string &str, const std::string &subStr);
std::vector<QString> StrSplitQt(const QString &str, const QString &delimiter);
QString StrDivideQt(const QString &str, const int64_t &idx);
QString StrMergeQt(const char* format, ...);
QString GetPrevStringQt(const QString &str, const QChar &chr);
QString GetRePrevStringQt(const QString &str, const QChar &chr);
QString GetPostStringQt(const QString &str, const QChar &chr);
QString GetRePostStringQt(const QString &str, const QChar &chr);
QString ReplaceStringQt(const QString &str, const QString &replaceStr);
uint64_t GetTimeStampMs();
