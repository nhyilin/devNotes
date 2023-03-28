#include "themewidget.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMessageBox>
#include <QProcessEnvironment>
#include <QInputDialog>

#if defined(_MSC_VER)&&(_MSC_VER >= 1600)
#pragma execution_character_set("utf-8")
#endif

int main(int argc, char *argv[]) {

    QProcessEnvironment::systemEnvironment().insert("QT_AUTO_SCREEN_SCALE_FACTOR", "1");

#if (QT_VERSION>=QT_VERSION_CHECK(5,6,0))
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication a(argc, argv);
    QMainWindow window;

    QString username = "admin";
    QString password = "admin";
    QString inputUsername = "";
    QString inputPassword = "";
    bool loginSuccess = false;
    while (!loginSuccess) {
        inputUsername = QInputDialog::getText(&window, "Login", "Username:");
        inputPassword = QInputDialog::getText(&window, "Login", "Password:", QLineEdit::Password);
        if (inputUsername == username && inputPassword == password) {
            loginSuccess = true;
        }
        else {
            QMessageBox::warning(&window, "Login Failed", "Invalid username or password. Please try again.");
        }
    }
    window.close();

    ThemeWidget *widget = new ThemeWidget();
    window.setCentralWidget(widget);
    window.resize(900, 600);
    window.setWindowTitle("电梯健康评估监测");
    window.show();
    return a.exec();
}
