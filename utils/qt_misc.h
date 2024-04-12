#pragma once

#include "libcu.h"
#include <QAbstractItemView>
#include <QAction>
#include <QApplication>
#include <QBuffer>
#include <QByteArray>
#include <QCloseEvent>
#include <QCompleter>
#include <QContextMenuEvent>
#include <QCoreApplication>
#include <QDialog>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QFrame>
#include <QGraphicsDropShadowEffect>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMenu>
#include <QMessageBox>
#include <QMouseEvent>
#include <QObject>
#include <QPixmap>
#include <QProgressDialog>
#include <QPushButton>
#include <QResizeEvent>
#include <QStandardPaths>
#include <QString>
#include <QStringListModel>
#include <QTimer>
#include <QVBoxLayout>
#include <QWebEngineDownloadRequest>
#include <QWebEngineFullScreenRequest>
#include <QWebEngineHistory>
#include <QWebEnginePage>
#include <QWebEngineProfile>
#include <QWebEngineSettings>
#include <QWebEngineUrlRequestJob>
#include <QWebEngineUrlScheme>
#include <QWebEngineUrlSchemeHandler>
#include <QWebEngineView>
#include <QWidget>

inline int64_t GetTimeStampMsQt()
{
	auto time_pt = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
	return time_pt.time_since_epoch().count();
}
