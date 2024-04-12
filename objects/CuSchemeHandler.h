#pragma once

#include "utils/qt_misc.h"
#include "utils/CuLogger.h"
#include "widgets/CuWebView.h"


class CuSchemeHandler : public QWebEngineUrlSchemeHandler
{
    Q_OBJECT
    public:
        explicit CuSchemeHandler(QObject* parent);
        ~CuSchemeHandler();
        void requestStarted(QWebEngineUrlRequestJob* job) override;

    private:
        QString GetBookmarkHtml_();
        QString GetAboutHtml_();
        QString GetHistoryHtml_();
};
