#include "TBASMainWindow/TBASMainWindow.hpp"

#include <QApplication>
#include <QCommandLineParser>

#ifndef APP_NAME
	#define APP_NAME ""
#endif // APP_NAME

#ifndef VERSION_STR
	#define VERSION_STR ""
#endif // VERSION_STR

#define DATABASE_PATH "/var/TBAS/clean.amdz"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	// Command line parse
	QCoreApplication::setApplicationName(APP_NAME);
	QCoreApplication::setApplicationVersion(VERSION_STR);
	QCommandLineParser parser;
  parser.setApplicationDescription(QString("Программное обеспечение для администрирования средств доверенной загрузки"));
	parser.addHelpOption();
	parser.addVersionOption();
  QCommandLineOption databasePathOption(QStringList() << "p" << "database-path",
                                  QString("<Путь> до базы данных СДЗ, по умолчанию: %1").arg(DATABASE_PATH),
                                  QString("path"),
                                  QString(DATABASE_PATH));
  parser.addOption(databasePathOption);

	parser.process(app);

	// Start program
	MainWindow mainWindow;
  mainWindow.setUp(QStringList() 	<< parser.value(databasePathOption));
	mainWindow.show();
	return app.exec();
}
