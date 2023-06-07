#pragma once

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>

class CuTabButton : public QPushButton
{
    Q_OBJECT
    public:
        explicit CuTabButton(QWidget* parent);
        ~CuTabButton();
        void SetFocused(bool focused);

    signals:
        void MouseLeftButtonClicked(CuTabButton* tabButton);
        void MouseRightButtonClicked(CuTabButton* tabButton);

    protected:
        void mousePressEvent(QMouseEvent* event) override;

};
