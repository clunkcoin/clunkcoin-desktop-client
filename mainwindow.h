#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "walletwindow.h"  // Include the WalletWindow header
#include "auth_interface.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void authButton_clicked();  // Slot for handling the login button click
    void createAccountButton_clicked();

private:
    Ui::MainWindow *ui;
    WalletWindow *walletWindow;  // Pointer to the WalletWindow
    void handleAuthenticationResult(const ExportedCredentials& result);
};

#endif // MAINWINDOW_H
