#ifndef WALLETWINDOW_H
#define WALLETWINDOW_H

#include <QMainWindow>

namespace Ui {
class WalletWindow;
}

class WalletWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit WalletWindow(QWidget *parent = nullptr);
    ~WalletWindow();

private slots:
    void generateBankStatement(); // Function to generate PDF

private:
    Ui::WalletWindow *ui;
};

#endif // WALLETWINDOW_H
