#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "walletwindow.h"  // Include the WalletWindow header

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

private:
    Ui::MainWindow *ui;
    WalletWindow *walletWindow;  // Pointer to the WalletWindow
};

#endif // MAINWINDOW_H
