#include "advancedoptionsdialog.h"

AdvancedOptionsDialog::AdvancedOptionsDialog(Options & options, QWidget * parent) :
    QDialog(parent), options{options}
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    this->gridMainWrapper = new QGridLayout;
    this->buildOptionsPanel();
    this->buildButtonGroup();
    this->setLayout(this->gridMainWrapper);
    this->addEvents();
}

void AdvancedOptionsDialog::validate(){
    QString primeNumbers{this->inputNumberOfPrimes->text()};

    if (QRegularExpression("^[0-9]+$").match(primeNumbers).hasMatch()){
        this->options.primeRange = primeNumbers.toLong();
    }

    this->accept();
}

void AdvancedOptionsDialog::toggelingGrouping(){
    this->options.grouping = !this->options.grouping;
    this->toggleGrouping->setText(this->options.grouping ? fa::TOGGLE_ON : fa::TOGGLE_OFF);
}

void AdvancedOptionsDialog::buildOptionsPanel(){
    this->title               = new QLabel{"Advanced Options"};
    this->contentBox          = new QGroupBox;
    QGridLayout * layout      = new QGridLayout;
    this->labelGrouping       = new QLabel{"Grouping:"};
    this->labelNumberOfPrimes = new QLabel{"Max size of primenumbers:"};
    this->toggleGrouping      = new QPushButton{this->options.grouping ? fa::TOGGLE_ON : fa::TOGGLE_OFF};
    this->inputNumberOfPrimes = new QLineEdit(QString("%1").arg(this->options.primeRange));

    this->toggleGrouping->setToolTip("Two characters will be grouped together. Not all keys will work with this option on.");
    this->inputNumberOfPrimes->setToolTip("The range of how many prime numbers are available in the key generation dialog.");

    layout->addWidget(this->labelGrouping,       0, 0);
    layout->addWidget(this->toggleGrouping,      0, 1);
    layout->addWidget(this->labelNumberOfPrimes, 1, 0);
    layout->addWidget(this->inputNumberOfPrimes, 1, 1);

    this->contentBox->setLayout(layout);
    this->gridMainWrapper->addWidget(this->title, 0, 0, Qt::AlignCenter);
    this->gridMainWrapper->addWidget(this->contentBox, 1, 0);
}

void AdvancedOptionsDialog::buildButtonGroup(){
    QHBoxLayout * layout = new QHBoxLayout;
    this->buttonBox      = new QGroupBox;
    this->btnAccept      = new QPushButton(fa::CHECK);
    this->btnReject      = new QPushButton(fa::TIMES);

    layout->addWidget(this->btnAccept);
    layout->addWidget(this->btnReject);

    this->btnAccept->setToolTip("Accept new keys");
    this->btnReject->setToolTip("Cancel");
    this->buttonBox->setLayout(layout);
    this->gridMainWrapper->addWidget(this->buttonBox, 2, 0);
}

void AdvancedOptionsDialog::addEvents(){
    connect(this->btnAccept, SIGNAL(clicked()), this, SLOT(validate()));
    connect(this->btnReject, SIGNAL(clicked()), this, SLOT(reject()));
    connect(this->toggleGrouping, SIGNAL(clicked()), this, SLOT(toggelingGrouping()));
}
