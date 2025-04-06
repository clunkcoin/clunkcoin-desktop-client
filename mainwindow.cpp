#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->btn_authenticate, &QPushButton::clicked, this, &MainWindow::authButton_clicked);
}

MainWindow::~MainWindow() {
    delete ui;
}

// Slot to handle the auth button click
void MainWindow::authButton_clicked() {
    // Here, you can add your authentication logic (e.g., checking credentials)
    if (true) { // Replace with actual authentication logic
        walletWindow = new WalletWindow();  // Create the WalletWindow
        walletWindow->show();  // Show the WalletWindow
        this->close();  // Close the authentication screen (MainWindow)
    }
}
