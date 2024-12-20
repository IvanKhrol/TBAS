#include "TBASAuthorizationWidget.hpp"
#include "externals/ErrorMessageBox.hpp"
#include "ui_TBASAuthorizationWidget.h"

TBASAuthorizationWidget::TBASAuthorizationWidget(QWidget *parent) :
  QWidget(parent), ui(new Ui::TBASAuthorizationWidget) {
  qDebug() << DPREFIX"Start create TBASAuthorizationWidget";
  ui->setupUi(this);

  connect(ui->okButton, &QPushButton::clicked,
          this, &TBASAuthorizationWidget::checkAuth);

  qDebug() << DPREFIX"End create TBASAuthorizationWidget";
}

// Главная функция настройки виджета
int TBASAuthorizationWidget::setUp() {
  int res = 0;
  if(res != 0) {
    emit error(res);
  }
  return res;
}

// Проверка корреткности авторизации
const void TBASAuthorizationWidget::checkAuth() {
  qDebug() << DPREFIX"Start checkAuth";
  auto tmidStr = ui->userTmidEdit->text();
  if(tmidStr.length() != TMID_LENGHT) {
    ErrorMessageBox errorMessageBox(QString(tr("Wrong lenght tmid")),
                                     QString(tr("Tmid: <strong>%1</strong> has wrong lenght!").arg(
                                                  tmidStr)));
    errorMessageBox.exec();
    qCritical() << CPREFIX"Wrong lenght tmid";
    emit error(-1);
    return;
  }
  if(tmidStr == QString(TEST_TMID)) {
    if(ui->passwordEdit->text() == QString(TEST_PASS)) {
      emit auth_ok();
      return;
    } else {
      ErrorMessageBox errorMessageBox(QString(tr("Wrong password")),
                                       QString(tr("Wrong password for this tmid")));
      errorMessageBox.exec();
      qCritical() << CPREFIX"Wrong password";
      emit error(-1);
      return;
    }
  }
}

TBASAuthorizationWidget::~TBASAuthorizationWidget() {
  qDebug() << DPREFIX"Delete TBASAuthorizationWidget";
}
