#pragma once

#include <iostream>
#include "utils/utils.h"
#include "utils/JsonObject.h"

#include <QObject>
#include <QFile>
#include <QBuffer>
#include <QWebEngineUrlSchemeHandler>
#include <QWebEngineUrlRequestJob>

class CuSchemeHandler : public QWebEngineUrlSchemeHandler
{
    Q_OBJECT
    public:
        explicit CuSchemeHandler(const QString &path);
        ~CuSchemeHandler();
        void requestStarted(QWebEngineUrlRequestJob* job) override;

    private:
        QString path_;

        QString GetBookmarkHtml_();
        void DeleteBookmark_(const QString &id);
};
