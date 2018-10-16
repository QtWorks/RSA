#ifndef ADVANCEDOPTIONSDIALOG_H
#define ADVANCEDOPTIONSDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRegularExpression>

#include "faicons.h"
#include "options.h"

class AdvancedOptionsDialog : public QDialog
{
    Q_OBJECT
public:
    AdvancedOptionsDialog(Options &, QWidget * parent = nullptr);

private slots:
    void validate();
    void toggelingGrouping();

private:
    void buildOptionsPanel();
    void buildButtonGroup();
    void addEvents();

    Options     &options;

    QGridLayout *gridMainWrapper;
    QLabel      *title;

    QGroupBox   *contentBox;
    QLabel      *labelGrouping;
    QLabel      *labelNumberOfPrimes;
    QPushButton *toggleGrouping;
    QLineEdit   *inputNumberOfPrimes;

    QGroupBox   *buttonBox;
    QPushButton *btnAccept;
    QPushButton *btnReject;
};

#endif // ADVANCEDOPTIONSDIALOG_H
