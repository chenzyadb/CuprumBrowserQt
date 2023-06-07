#include "widgets/CuTabButton.h"

constexpr char unfocusedButtonStyle[] =
    "QPushButton {                                                               "
    "   border: none;                                                            "
    "   background-color: #F8F8F8;                                               "
    "   color: #000000;                                                          "
    "   text-align: left;                                                        "
    "   font-size: 12px;                                                         "
    "   padding-left: 10px;                                                      "
    "   padding-right: 10px;                                                     "
    "   border-radius: 5px;                                                      "
    "}                                                                           "
    "QPushButton:hover {                                                         "
    "   background-color: #F0F0F0;                                               "
    "}                                                                           "
    "QPushButton:pressed {                                                       "
    "   background-color: #E8E8E8;                                               "
    "}                                                                           ";

constexpr char focusedButtonStyle[] =
    "QPushButton {                                                               "
    "   border: none;                                                            "
    "   background-color: #000000;                                               "
    "   color: #FFFFFF;                                                          "
    "   text-align: left;                                                        "
    "   font-size: 12px;                                                         "
    "   padding-left: 10px;                                                      "
    "   padding-right: 10px;                                                     "
    "   border-radius: 5px;                                                      "
    "}                                                                           "
    "QPushButton:hover {                                                         "
    "   background-color: #202020;                                               "
    "}                                                                           "
    "QPushButton:pressed {                                                       "
    "   background-color: #404040;                                               "
    "}                                                                           ";

CuTabButton::CuTabButton(QWidget* parent) : QPushButton(parent)
{
    setMinimumHeight(30);
    setMaximumHeight(30);
    setMinimumWidth(50);
    setMaximumWidth(200);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    SetFocused(false);
}

CuTabButton::~CuTabButton() { }

void CuTabButton::SetFocused(bool focused)
{
    if (focused) {
        setStyleSheet(focusedButtonStyle);
    } else {
        setStyleSheet(unfocusedButtonStyle);
    }
}

void CuTabButton::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        emit MouseLeftButtonClicked(this);
    } else if (event->button() == Qt::RightButton) {
        emit MouseRightButtonClicked(this);
    }
}
