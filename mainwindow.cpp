#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), walletWindow(nullptr) {
    ui->setupUi(this);

    connect(ui->btn_authenticate, &QPushButton::clicked, this, &MainWindow::authButton_clicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::createAccountButton_clicked);
}

MainWindow::~MainWindow() {
    delete ui;
    if (walletWindow) {
        delete walletWindow;
    }
}

void MainWindow::handleAuthenticationResult(const ExportedCredentials& result) {
    if (result.success) {
        walletWindow = new WalletWindow();
        // Here you can pass the credentials to the wallet window if needed
        walletWindow->show();
        this->close();
    } else {
        QMessageBox::critical(this, "Authentication Error", 
            QString("Authentication failed: %1").arg(result.error));
    }
}

void MainWindow::authButton_clicked() {
    QString password = ui->lineEdit_3->text();
    QString pin = ui->lineEdit_4->text();
    QString routingNumber = ui->lineEdit->text();
    QString accountNumber = ui->lineEdit_2->text();

    if (password.isEmpty() || pin.isEmpty() || routingNumber.isEmpty() || accountNumber.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all fields");
        return;
    }

    ExportedCredentials result = verifyReturningUser(
        password.toUtf8().constData(),
        pin.toUtf8().constData(),
        routingNumber.toUtf8().constData(),
        accountNumber.toUtf8().constData()
    );

    // Show the credentials in a message box
    QString credentialsMessage = QString(
        "Authentication Result:\n\n"
        "Success: %1\n"
        "Routing Number: %2\n"
        "Account Number: %3\n"
        "Public Key Length: %4\n"
        "Private Key Length: %5\n"
        "Error (if any): %6\n\n"
        "Public Key (hex): %7\n"
        "Private Key (hex): %8"
    )
    .arg(result.success ? "Yes" : "No")
    .arg(result.routing_number)
    .arg(result.account_number)
    .arg(result.public_key_len)
    .arg(result.private_key_len)
    .arg(result.error)
    .arg(QString::fromLatin1(QByteArray((char*)result.public_key, result.public_key_len).toHex()))
    .arg(QString::fromLatin1(QByteArray((char*)result.private_key, result.private_key_len).toHex()));

    QMessageBox::information(this, "Authentication Details", credentialsMessage);

    handleAuthenticationResult(result);
}

void MainWindow::createAccountButton_clicked() {
    QString password = ui->lineEdit_5->text();
    QString pin = ui->lineEdit_6->text();
    QString routingNumber = ui->lineEdit_7->text();

    if (password.isEmpty() || pin.isEmpty() || routingNumber.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all fields");
        return;
    }

    ExportedCredentials result = createNewUser(
        password.toUtf8().constData(),
        pin.toUtf8().constData(),
        routingNumber.toUtf8().constData()
    );

    handleAuthenticationResult(result);
}
