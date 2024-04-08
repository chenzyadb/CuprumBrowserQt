#pragma once

#include "utils/qt_misc.h"

class CuTabButton : public QFrame
{
    Q_OBJECT
    public:
        explicit CuTabButton(QWidget* parent);
        ~CuTabButton();
        void setFocus(bool focused);
        void setIcon(const QIcon &icon);
        void setText(const QString &text);

    signals:
        void onClick(CuTabButton* tabButton);
        void onCommandClose(CuTabButton* tabButton);

    protected:
        void mousePressEvent(QMouseEvent* event) override;

    private:
        QHBoxLayout* buttonLayout_;
        QLabel* buttonIcon_;
        QLabel* buttonLabel_;
        QPushButton* buttonClose_;
};
