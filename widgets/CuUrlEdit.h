#pragma once

#include "utils/qt_misc.h"
#include "utils/browser_misc.h"

class CuUrlEdit : public QLineEdit
{
	Q_OBJECT
	public:
		CuUrlEdit(QWidget* parent);
		~CuUrlEdit();

	protected:
		void focusInEvent(QFocusEvent* event) override;

	private:
		void setUrlCompeleter_();
};
