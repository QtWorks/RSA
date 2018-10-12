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

shared_ptr<rsa::Key> KeyGenerationDialog::getKey(){
    if (this->resultKey == nullptr){
        return std::make_shared<rsa::Key>();
    }
    return this->resultKey;
}

/*
[int64]$validator = ([int64]$box_p.Text - 1) * ([int64]$box_q.Text - 1)
if ( (Get-GGT -First ([int64]$txt_e.Text) -Second $validator) -ne 1) { return }
$txt_d.Text = extendedGcd ([int64]$txt_e.Text) ([int64]$validator)
$txt_publicKey.Text = $txt_e.Text + "," + $txt_n.Text
$txt_privateKey.Text = $txt_d.Text + "," + $txt_n.Text
*/
void KeyGenerationDialog::recalculateKey(const QString & number){
    qint64 p         {this->chooserP->currentText().toLongLong()};
    qint64 q         {this->chooserQ->currentText().toLongLong()};
    qint64 e         {this->chooserE->currentText().toLongLong()};
    qint64 validator {(p - 1) * (q - 1)};

    if (1 != rsa::ggt(e, validator)){
        this->resultN->setText("Invalid");
        this->resultD->setText("Invalid");
        return;
    }

    int64 n {p * q};
    int64 d {rsa::extendedGcd(e, validator)};

    this->resultKey = std::make_shared<rsa::Key>(e, d, n);
    this->resultN->setText(QString("%1").arg(n));
    this->resultD->setText(QString("%1").arg(d));
}

void KeyGenerationDialog::buildKeyPanel(){
    this->title          = new QLabel{"Key Generation"};

    //Actual user input
    this->contentBox     = new QGroupBox;
    QGridLayout * layout = new QGridLayout;
    this->labelP         = new QLabel{"P:"};
    this->labelQ         = new QLabel{"Q:"};
    this->labelE         = new QLabel{"E:"};
    this->chooserP       = new QComboBox;
    this->chooserQ       = new QComboBox;
    this->chooserE       = new QComboBox;

    //Just for visualisation
    this->labelN         = new QLabel{"N:"};
    this->labelD         = new QLabel{"D:"};
    this->resultN        = new QLineEdit;
    this->resultD        = new QLineEdit;

    this->resultN->setEnabled(false);
    this->resultD->setEnabled(false);

    layout->addWidget(this->labelP,   0, 0);
    layout->addWidget(this->chooserP, 0, 1);
    layout->addWidget(this->labelQ,   1, 0, 2, 1, Qt::AlignCenter);
    layout->addWidget(this->chooserQ, 1, 1, 2, 1, Qt::AlignCenter);
    layout->addWidget(this->labelE,   3, 0);
    layout->addWidget(this->chooserE, 3, 1);

    layout->addWidget(this->labelN,   0, 2, 2, 1, Qt::AlignCenter);
    layout->addWidget(this->resultN,  0, 3, 2, 1, Qt::AlignCenter);
    layout->addWidget(this->labelD,   2, 2, 2, 1, Qt::AlignCenter);
    layout->addWidget(this->resultD,  2, 3, 2, 1, Qt::AlignCenter);

    this->contentBox->setLayout(layout);
    this->gridMainWrapper->addWidget(this->title, 0, 0, Qt::AlignCenter);
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
        this->chooserE->addItem(QString("%1").arg(prime));
    }
    this->recalculateKey(nullptr);
}

void KeyGenerationDialog::addEvents(){
    connect(this->btnAccept, SIGNAL(clicked()), this, SLOT(accept()));
    connect(this->btnReject, SIGNAL(clicked()), this, SLOT(reject()));
    connect(this->chooserP, SIGNAL(currentTextChanged(const QString &)), this, SLOT(recalculateKey(const QString &)));
    connect(this->chooserQ, SIGNAL(currentTextChanged(const QString &)), this, SLOT(recalculateKey(const QString &)));
    connect(this->chooserE, SIGNAL(currentTextChanged(const QString &)), this, SLOT(recalculateKey(const QString &)));
}
