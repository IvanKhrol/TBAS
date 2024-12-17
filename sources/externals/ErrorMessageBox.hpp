#ifndef ERROR_MESSAGE_BOX_HPP
#define  ERROR_MESSAGE_BOX_HPP


#include <QMessageBox>

class ErrorMessageBox : public QMessageBox {
public:
  ErrorMessageBox(const QString& title, const QString& text, QWidget *parent = nullptr)
      : QMessageBox(parent) {
      setWindowTitle(title);
      setText(text);
      setIcon(QMessageBox::Critical);
      setStandardButtons(QMessageBox::Ok);
      setDefaultButton(QMessageBox::Ok);
  }
};

#endif // ERROR_MESSAGE_BOX_HPP