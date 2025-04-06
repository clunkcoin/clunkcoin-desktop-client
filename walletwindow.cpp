#include "walletwindow.h"
#include "ui_walletwindow.h"
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QDebug>

WalletWindow::WalletWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::WalletWindow) {
    ui->setupUi(this);

    // Connect a button to trigger PDF generation
    connect(ui->generatePdfButton, &QPushButton::clicked, this, &WalletWindow::generateBankStatement);
}

WalletWindow::~WalletWindow() {
    delete ui;
}

void WalletWindow::generateBankStatement() {
    QString filePath = QFileDialog::getSaveFileName(this, "Save PDF", "", "PDF Files (*.pdf)");
    if (filePath.isEmpty()) {
        return;
    }

    QPdfWriter pdfWriter(filePath);
    pdfWriter.setPageSize(QPageSize::A4);
    pdfWriter.setResolution(300);

    QPainter painter(&pdfWriter);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setFont(QFont("Arial", 12));

    int leftMargin = 50;
    int topMargin = 50;
    int lineHeight = 50;
    int yPos = topMargin;

    // Draw bank logo (Ensure your logo is in Qt resources)
    QImage logo(":/logo_app7575.png");
    painter.drawImage(QRect(leftMargin, yPos, 100, 100), logo);

    // Title
    painter.setFont(QFont("Arial", 16, QFont::Bold));
    painter.drawText(leftMargin + 120, yPos + 80, "CLUNKCOIN Statement");

    painter.drawLine(leftMargin, yPos + 110, 2000, yPos + 110);


    yPos += 130;


    // Account Details
    painter.setFont(QFont("Arial", 12));
    // painter.drawText(leftMargin, yPos, "Account Holder: John Doe");
    painter.drawText(leftMargin, yPos + lineHeight, "Routing Number: 465437766479");
    painter.drawText(leftMargin, yPos + 2 * lineHeight, "Account Number: 76776546");
    painter.drawText(leftMargin, yPos + 3 * lineHeight, "Statement Date: 2025-04-01");

    yPos += 5 * lineHeight; // Add some space before transactions



    // Table Headers
    int tableStartY = yPos;
    int col1 = leftMargin;
    int col2 = col1 + 400;
    int col3 = col2 + 400;
    int col4 = col3 + 300;
    int col5 = col4 + 500;
    int rowHeight = 50;

    painter.setFont(QFont("Arial", 12, QFont::Bold));
    painter.drawText(col1, yPos, "Date");
    painter.drawText(col2, yPos, "Type");
    painter.drawText(col3, yPos, "Amount");
    painter.drawText(col4, yPos, "Routing Number");
    painter.drawText(col5, yPos, "Account Number");

    yPos += rowHeight;

    // Draw line under headers
    painter.drawLine(leftMargin, yPos - 40, col5 + 300, yPos - 40);
    yPos += 10;

    // Transaction Entries
    painter.setFont(QFont("Arial", 12));
    QStringList transactions = {
        "2025-03-30;Sent;-50.00;674737222;54724822",
        "2025-03-28;Received;200.00;87583828282;55324542"
    };

    for (const QString &entry : transactions) {
        QStringList fields = entry.split(";");
        if (fields.size() == 5) {
            painter.drawText(col1, yPos, fields[0]);  // Date
            painter.drawText(col2, yPos, fields[1]);  // type
            painter.drawText(col3, yPos, fields[2]);  // Amount
            painter.drawText(col4, yPos, fields[3]);  // Routing Number
            painter.drawText(col5, yPos, fields[4]);  // Account Number
        }
        yPos += rowHeight;
    }

    // Draw line under transactions
    yPos += 10;
    painter.drawLine(leftMargin, yPos - 15, col5 + 300, yPos - 15);

    // Closing Balance
    yPos += 30;
    painter.setFont(QFont("Arial", 12, QFont::Bold));
    painter.drawText(col1, yPos, "Closing Balance:");
    painter.drawText(col3, yPos, "150.00");

    painter.end();
    qDebug() << "Bank statement PDF saved at:" << filePath;
}

