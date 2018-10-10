#ifndef KEYGENERATIONDIALOG_H
#define KEYGENERATIONDIALOG_H

#include <QComboBox>
#include <QDialog>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include "faicons.h"

class KeyGenerationDialog : public QDialog
{
    Q_OBJECT
public:
    KeyGenerationDialog(QWidget * parent = nullptr);

private:
    void buildKeyPanel();
    void buildButtonGroup();
    void fillPrimeBoxes();
    void addEvents();

    QGridLayout *gridMainWrapper;
    QLabel      *title;

    QGroupBox   *contentBox;
    QLabel      *labelP;
    QLabel      *labelQ;
    QComboBox   *chooserP;
    QComboBox   *chooserQ;

    QGroupBox   *buttonBox;
    QPushButton *btnAccept;
    QPushButton *btnReject;
};

#endif // KEYGENERATIONDIALOG_H
