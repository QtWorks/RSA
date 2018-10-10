#include "keygenerationdialog.h"

shared_ptr<vector<int64>>KeyGenerationDialog::primes = rsa::calculateSieveOfEratosthenes(100ll);

KeyGenerationDialog::KeyGenerationDialog(QWidget * parent) :
    QDialog(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    this->gridMainWrapper = new QGridLayout;
    this->buildKeyPanel();
    this->buildButtonGroup();
    this->fillPrimeBoxes();
    this->setLayout(this->gridMainWrapper);
    this->addEvents();
}

void KeyGenerationDialog::buildKeyPanel(){
    this->title          = new QLabel{"Key Generation"};
    this->contentBox     = new QGroupBox;
    QGridLayout * layout = new QGridLayout;
    this->labelP         = new QLabel{"P:"};
    this->labelQ         = new QLabel{"Q:"};
    this->chooserP       = new QComboBox;
    this->chooserQ       = new QComboBox;

    layout->addWidget(this->labelP,   0, 0);
    layout->addWidget(this->chooserP, 0, 1);
    layout->addWidget(this->labelQ,   1, 0);
    layout->addWidget(this->chooserQ, 1, 1);

    this->contentBox->setLayout(layout);
    this->gridMainWrapper->addWidget(this->title, 0, 0);
    this->gridMainWrapper->addWidget(this->contentBox, 1, 0);
}

void KeyGenerationDialog::buildButtonGroup(){
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

void KeyGenerationDialog::fillPrimeBoxes(){
    this->chooserP->setView(new QListView);
    this->chooserQ->setView(new QListView);

    for (auto prime : *primes){
        this->chooserP->addItem(QString("%1").arg(prime));
        this->chooserQ->addItem(QString("%1").arg(prime));
    }
}

void KeyGenerationDialog::addEvents(){
    connect(this->btnAccept, SIGNAL(clicked()), this, SLOT(accept()));
    connect(this->btnReject, SIGNAL(clicked()), this, SLOT(reject()));
}
