#ifndef TBAS_AUTHORIZATION_WIDGET_HPP
#define TBAS_AUTHORIZATION_WIDGET_HPP

#include <QWidget>
#include <QScopedPointer>

#include <QDebug>
#ifdef DPREFIX
  #undef DPREFIX
#endif // DPREFIX
#define DPREFIX "Authorization Widget DEBUG: "

#ifdef CPREFIX
  #undef CPREFIX
#endif // CPREFIX
#define CPREFIX "Authorization Widget ERROR!\n\t"


#define TMID_LENGHT 16
#define TEST_TMID "123456789ABCDEF0"
#define TEST_PASS "1234"

namespace Ui {
class TBASAuthorizationWidget;
}

class TBASAuthorizationWidget : public QWidget {
  Q_OBJECT

public:
  explicit TBASAuthorizationWidget(QWidget *parent = nullptr);
  ~TBASAuthorizationWidget();

  int setUp();

signals:
  void error(int err);
  void auth_ok();

private:
  QScopedPointer<Ui::TBASAuthorizationWidget> ui;

private slots:
  const void checkAuth();
};

#endif // TBAS_AUTHORIZATION_WIDGET_HPP
