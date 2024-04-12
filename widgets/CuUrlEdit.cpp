#include "CuUrlEdit.h"

constexpr char urlEditStyle[] = 
	"CuUrlEdit {                                                                 "
	"   border: none;                                                            "
	"   background-color: #F0F0F0;                                               "
	"   color: #000000;                                                          "
	"   font-size: 14px;                                                         "
	"   border-radius: 5px;                                                      "
	"   padding-left: 5px;                                                       "
	"   padding-right: 5px;                                                      "
	"}                                                                           "
	"CuUrlEdit:hover {                                                           "
	"   background-color: #E8E8E8;                                               "
	"}                                                                           "
	"CuUrlEdit:pressed {                                                         "
	"   background-color: #E8E8E8;                                               "
	"}                                                                           ";

constexpr char popupStyle[] =
	"QAbstractItemView {                                                         "
	"	margin-top: 5px;                                                         "
	"   background-color: #F0F0F0;                                               "
	"   font-size: 14px;                                                         "
	"   color: #000000;                                                          "
	"}                                                                           ";

CuUrlEdit::CuUrlEdit(QWidget* parent) : QLineEdit(parent) 
{ 
	setStyleSheet(urlEditStyle);
}

CuUrlEdit::~CuUrlEdit() { }

void CuUrlEdit::focusInEvent(QFocusEvent* event)
{
	QLineEdit::focusInEvent(event);
	if (event->reason() == Qt::MouseFocusReason) {
		QTimer::singleShot(0, this, [this]() {
			selectAll();
			setUrlCompeleter_();
		});
	}
}

void CuUrlEdit::setUrlCompeleter_()
{
	auto urlCompleter = new QCompleter(this);
	auto completerModel = new QStringListModel(urlCompleter);
	{
		QList<QString> urlList{};
		auto historyItems = HistoryProvider::GetHistoryItems();
		for (const auto &item : historyItems) {
			urlList.emplace_back(item.url);
		}
		auto bookmarks = BookmarkProvider::GetBookmarks();
		for (const auto &bookmark : bookmarks) {
			urlList.emplace_back(bookmark.url);
		}
		completerModel->setStringList(urlList);
	}
	urlCompleter->setModel(completerModel);
	urlCompleter->setCaseSensitivity(Qt::CaseSensitive);
	urlCompleter->setFilterMode(Qt::MatchContains);
	urlCompleter->setCompletionMode(QCompleter::PopupCompletion);
	urlCompleter->setMaxVisibleItems(5);
	urlCompleter->popup()->setStyleSheet(popupStyle);
	setCompleter(urlCompleter);
}
