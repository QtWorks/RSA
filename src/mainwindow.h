#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFontDatabase>
#include <QDebug>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QProgressBar>
#include <QFileDialog>

#include "advancedoptionsdialog.h"
#include "faicons.h"
#include "keygenerationdialog.h"
#include "options.h"
#include "rsa.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void encrypt();
    void decrypt();
    void loadFile();
    void saveFile();
    void showKeyGenerationDialog();
    void showAdvancedOptionsDialog();

private:
    QFont* loadFont(QString);
    void buildKeyPanel();
    void buildMainContent();
    void buildExtras();
    void addEvents();

    Options       options;

    QGroupBox    *groupBoxMainWrapper;
    QGridLayout  *gridMainWrapper;

    QLineEdit    *publicE;
    QLineEdit    *publicN;
    QLineEdit    *privateD;
    QLineEdit    *privateN;
    QPushButton  *btnShowKeyGenerationPanel;
    QPushButton  *btnShowMoreOptions;

    QTextEdit    *txtInputText;
    QTextEdit    *txtEncryptedText;
    QTextEdit    *txtDecryptedText;
    QPushButton  *btnEncrypt;
    QPushButton  *btnDecrypt;
    QPushButton  *btnLoadFile;
    QPushButton  *btnSaveFile;

    QProgressBar *progressBar;
};

#endif // MAINWINDOW_H
