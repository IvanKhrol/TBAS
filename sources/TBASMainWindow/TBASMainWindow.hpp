#ifndef TBAS_MAINWINDOW_HPP
#define TBAS_MAINWINDOW_HPP

#include <QMainWindow>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QLabel>

#include <QDebug>

#include "TBASAuthorizationWidget/TBASAuthorizationWidget.hpp"

#if defined(Q_OS_WIN)
  #include <Windows.h>
#endif

#ifdef DPREFIX
  #undef DPREFIX
#endif // DPREFIX
#define DPREFIX "Main Window DEBUG: "

#ifdef CPREFIX
  #undef CPREFIX
#endif // CPREFIX
#define CPREFIX "Main Window Critical ERROR!\n\t"

QT_BEGIN_NAMESPACE
namespace Ui {
  class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void setUp(const QStringList args);

private:
  QScopedPointer<Ui::MainWindow> ui;
  QScopedPointer<TBASAuthorizationWidget> authorizationWidget;
  QCheckBox *activateCheckBox;
  
  #if defined(Q_OS_WIN)
    void UpPrivilege();
  #endif

};

#endif // TBAS_MAINWINDOW_HPP
