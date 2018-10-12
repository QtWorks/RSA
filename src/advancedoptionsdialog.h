#ifndef ADVANCEDOPTIONSDIALOG_H
#define ADVANCEDOPTIONSDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>

#include "faicons.h"

struct Options
{
    bool grouping;
    Options() : Options(false){}
    Options(const bool grouping) : grouping{grouping}{}
};

class AdvancedOptionsDialog : public QDialog
{
    Q_OBJECT
public:
    AdvancedOptionsDialog(Options &, QWidget * parent = nullptr);

private slots:
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
    QPushButton *toggleGrouping;

    QGroupBox   *buttonBox;
    QPushButton *btnAccept;
    QPushButton *btnReject;
};

#endif // ADVANCEDOPTIONSDIALOG_H
