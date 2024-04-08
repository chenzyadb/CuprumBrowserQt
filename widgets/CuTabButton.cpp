#include "CuTabButton.h"

constexpr char buttonStyle[] =
    "CuTabButton {                                                               "
    "   border: none;                                                            "
    "   background-color: #FFFFFF;                                               "
    "   border-radius: 5px;                                                      "
    "}                                                                           "
    "CuTabButton:hover {                                                         "
    "   background-color: #F0F0F0;                                               "
    "}                                                                           "
    "QLabel {                                                                    "
    "   background-color: transparent;                                           "
    "   color: #000000;                                                          "
    "   text-align: left;                                                        "
    "   font-size: 12px;                                                         "
    "}                                                                           "
    "QPushButton {                                                               "
    "   border: none;                                                            "
    "   background-color: transparent;                                           "
    "   border-radius: 2px;                                                      "
    "}                                                                           "
    "QPushButton:hover {                                                         "
    "   background-color: #E0E0E0;                                               "
    "}                                                                           ";


CuTabButton::CuTabButton(QWidget* parent) : 
    QFrame(parent), 
    buttonLayout_(nullptr), 
    buttonLabel_(nullptr)
{
    setMinimumHeight(30);
    setMaximumHeight(30);
    setMinimumWidth(80);
    setMaximumWidth(200);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setStyleSheet(buttonStyle);
    {
        buttonLayout_ = new QHBoxLayout(this);
        buttonLayout_->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        buttonLayout_->setContentsMargins(5, 0, 5, 0);
        buttonLayout_->setSpacing(4);
        setLayout(buttonLayout_);
    }
    {
        buttonIcon_ = new QLabel(this);
        buttonIcon_->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        buttonLayout_->addWidget(buttonIcon_);
    }
    {
        buttonLabel_ = new QLabel(this);
        buttonLabel_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        buttonLayout_->addWidget(buttonLabel_);
    }
    {
        buttonClose_ = new QPushButton(this);
        buttonClose_->setFixedSize(16, 16);
        buttonClose_->setIcon(QIcon(":/res/media/close.png"));
        buttonClose_->setIconSize(QSize(12, 12));
        buttonClose_->setContentsMargins(0, 0, 0, 0);
        QObject::connect(buttonClose_, &QPushButton::clicked, this, [this]() {
            emit onCommandClose(this);
        });
        buttonLayout_->addWidget(buttonClose_);
    }
    setFocus(false);
}

CuTabButton::~CuTabButton() { }

void CuTabButton::setFocus(bool focused)
{
    auto shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setColor(Qt::gray);
    shadowEffect->setOffset(0, 0);
    if (focused) {
        shadowEffect->setBlurRadius(15.0);
        setGraphicsEffect(shadowEffect);
    } else {
        shadowEffect->setBlurRadius(0.0);
        setGraphicsEffect(shadowEffect);
    }
}

void CuTabButton::setIcon(const QIcon &icon)
{
    buttonIcon_->setPixmap(icon.pixmap(QSize(16, 16)));
}

void CuTabButton::setText(const QString &text)
{
    buttonLabel_->setText(text);
}

void CuTabButton::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        emit onClick(this);
    } else if (event->button() == Qt::RightButton) {
        emit onCommandClose(this);
    }
}
