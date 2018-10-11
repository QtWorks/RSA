#ifndef KEYGENERATIONDIALOG_H
#define KEYGENERATIONDIALOG_H

#include <QComboBox>
#include <QDialog>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QDebug>
#include <QListView>
#include <QHBoxLayout>
#include <QPushButton>

#include <memory>

#include "faicons.h"
#include "rsa.h"

class KeyGenerationDialog : public QDialog
{
    Q_OBJECT
public:
    KeyGenerationDialog(QWidget * parent = nullptr);

private slots:
    void recalculateKey(const QString &);

private:
    void buildKeyPanel();
    void buildButtonGroup();
    void fillPrimeBoxes();
    void addEvents();

    rsa::Key     resultKey;

    QGridLayout *gridMainWrapper;
    QLabel      *title;

    //Actual user input
    QGroupBox   *contentBox;
    QLabel      *labelP;
    QLabel      *labelQ;
    QLabel      *labelE;
    QComboBox   *chooserP;
    QComboBox   *chooserQ;
    QComboBox   *chooserE;

    //Just for visualisation
    QLabel      *labelN;
    QLabel      *labelD;
    QLineEdit   *resultN;
    QLineEdit   *resultD;

    QGroupBox   *buttonBox;
    QPushButton *btnAccept;
    QPushButton *btnReject;

    static shared_ptr<vector<int64>> primes;
};

#endif // KEYGENERATIONDIALOG_H
