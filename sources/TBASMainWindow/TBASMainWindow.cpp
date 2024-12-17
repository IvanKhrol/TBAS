#include "TBASMainWindow.hpp"
#include "ui_TBASMainWindow.h"

MainWindow::MainWindow(QWidget *parent):  
            QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  #if defined(Q_OS_WIN)
    UpPrivilege();
  #endif
}

#if defined(Q_OS_WIN)
  // Функция для поднятие привилегий программы для взаимодействия с UEFI-переменными
  void MainWindow::UpPrivilege() {
    qDebug() << DPREFIX"Start UpPrivilege ";

    try {
      HANDLE hToken = 0;
      TOKEN_PRIVILEGES tpNew;
      LUID luid1, luid2;
      bool result = true;

      qDebug() << DPREFIX"Call  OpenProcessToken";
      result = OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken);
      qDebug() << DPREFIX"OpenProcessToken result = " << result;

      qDebug() << DPREFIX"Call  LookupPrivilegeValue(SE_SYSTEM_ENVIRONMENT_NAME)";
      result = LookupPrivilegeValue(NULL, SE_SYSTEM_ENVIRONMENT_NAME, &luid1);
      qDebug() << DPREFIX"LookupPrivilegeValue result = " << result;

      qDebug() << DPREFIX"LookupPrivilegeValue(SE_SHUTDOWN_NAME)";
      result = LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &luid2);
      qDebug() << DPREFIX"LookupPrivilegeValue result = " << result;

      tpNew.PrivilegeCount = 1;		
      tpNew.Privileges[0].Attributes = 0x00000002; // SE_PRIVILEGE_ENABLED 
      tpNew.Privileges[0].Luid = luid1;		

      qDebug() << DPREFIX"Call  AdjustTokenPrivileges";
      result = AdjustTokenPrivileges(hToken, FALSE, &tpNew, sizeof(tpNew), NULL, NULL);
      qDebug() << DPREFIX"AdjustTokenPrivileges result = " << result;

      tpNew.PrivilegeCount = 1;
      tpNew.Privileges[0].Attributes = 0x00000002; // SE_PRIVILEGE_ENABLED 
      tpNew.Privileges[0].Luid = luid2;

      qDebug() << DPREFIX"Call  AdjustTokenPrivileges";
      result = AdjustTokenPrivileges(hToken, FALSE, &tpNew, sizeof(tpNew), NULL, NULL);
      qDebug() << DPREFIX"AdjustTokenPrivileges result = " << result;

      CloseHandle(hToken);
    }
    catch (...) {}

    qDebug() << DPREFIX"Out UpPrivilege"; 
  }
#endif

// Основная функция настройки виджета
void MainWindow::setUp(const QStringList args) {
  // Добавление виджета приветствия
  auto greetings_widget = new QLabel(this);
  greetings_widget->setText("Hello World!");
  greetings_widget->setAlignment(Qt::AlignCenter);
  qDebug() << DPREFIX"greetings widget ok";

  // Добавьте сочетание клавиш ctrl+q для выхода
  addAction(ui->actionClose);
  QObject::connect(ui->actionClose, &QAction::triggered, this, &QCoreApplication::quit);


  // Добавление виджетов в SwitchLayout
  ui->SwitchLayout->addWidget(greetings_widget);

  // Добавление действий в меню для смены виджета
  // QObject::connect(ui->actionOpenTypesWidget, &QAction::triggered,
  //   [this](){
  //     qDebug() << DPREFIX "actionOpenTypesWidget" ;
  //     if(ui->SwitchLayout->currentWidget() != typesWidget.get()) {
  //       ui->actionSavePorts->setEnabled(false);
  //       ui->actionSaveTypes->setEnabled(true);
        
  //       ui->SwitchLayout->setCurrentWidget(typesWidget.get());
  //       qDebug() << DPREFIX "set TypesWidget as Layout";
  //     }
  //   });
  // QObject::connect( ui->actionOpenPortsWidget, &QAction::triggered,
  //   [this](){
  //     qDebug() << DPREFIX "actionOpenPortsWidget" ;
  //     if(ui->SwitchLayout->currentWidget() != portsWidget.get()) {
  //       ui->actionSaveTypes->setEnabled(false);
  //       ui->actionSavePorts->setEnabled(true);

  //       ui->SwitchLayout->setCurrentWidget(portsWidget.get());
  //       qDebug() << DPREFIX "set PortsWidget as Layout";
  //     }
  //   });

  // Установите виджет приветствия по умолчанию
  ui->SwitchLayout->setCurrentWidget(greetings_widget);
  qDebug() << DPREFIX"end MainWindow SetUp";
}

MainWindow::~MainWindow() = default;
