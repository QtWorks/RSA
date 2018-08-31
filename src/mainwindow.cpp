#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent){
    this->groupBoxMainWrapper = new QGroupBox;
    this->gridMainWrapper     = new QGridLayout;
    this->groupBoxMainWrapper->setLayout(this->gridMainWrapper);
    this->buildExtras();
    this->buildKeyPanel();
    this->buildMainContent();
    this->buildExtras();
    this->setCentralWidget(this->groupBoxMainWrapper);
}

MainWindow::~MainWindow(){
}

void MainWindow::encrypt(){
    //TODO
}

void MainWindow::decrypt(){
    //TODO
}

void MainWindow::loadFile(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choose File"), "", tr("All Files (*)"));

    if (fileName.isEmpty()){
            return;
    } else {
        QFile       file{fileName};
        QTextStream in{&file};
        QString     content;

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            return;
        }

        while (!in.atEnd()) {
            content = in.readAll();
        }
        this->txtInputText->setText(content);
    }
}

void MainWindow::saveFile(){
    QString fileName = QFileDialog::getSaveFileName(this, tr("Choose file"), "", tr("All Files (*)"));

    if (fileName.isEmpty()){
            return;
    } else {
        QFile       file{fileName};
        QTextStream out{&file};

        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
            return;
        }
        out << this->txtDecryptedText->toPlainText();
    }
}

QFont* MainWindow::loadFont(QString fontFileName){
    int id = QFontDatabase::addApplicationFont(fontFileName);

    if (id < 0){
        qWarning() << fontFileName << " cannot be loaded !";
    }

    QString family = QFontDatabase::applicationFontFamilies(id).at(0);

    return new QFont(family);
}

void MainWindow::buildKeyPanel(){
    QGroupBox   *box           = new QGroupBox;
    QGridLayout *gridLayout    = new QGridLayout;
    QLabel      *labelPublicE  = new QLabel("Public E:");
    QLabel      *labelPublicN  = new QLabel("Public N:");
    QLabel      *labelPrivateD = new QLabel("Private D:");
    QLabel      *labelPrivateN = new QLabel("Private N:");
    this->publicE              = new QLineEdit("1721");
    this->publicN              = new QLineEdit("263713");
    this->privateD             = new QLineEdit("1373");
    this->privateN             = new QLineEdit("263713");

    gridLayout->addWidget(labelPublicE, 0, 0);
    gridLayout->addWidget(this->publicE, 0, 1);
    gridLayout->addWidget(labelPublicN, 0, 2);
    gridLayout->addWidget(this->publicN, 0, 3);
    gridLayout->addWidget(labelPrivateD, 1, 0);
    gridLayout->addWidget(this->privateD, 1, 1);
    gridLayout->addWidget(labelPrivateN, 1, 2);
    gridLayout->addWidget(this->privateN, 1, 3);
    box->setLayout(gridLayout);
    this->gridMainWrapper->addWidget(box, 0, 0);
}

void MainWindow::buildMainContent(){
    QGroupBox   *box        = new QGroupBox;
    QGridLayout *gridLayout = new QGridLayout;
    this->txtInputText      = new QTextEdit("Berlin");
    this->txtEncryptedText  = new QTextEdit;
    this->txtDecryptedText  = new QTextEdit;
    this->btnEncrypt        = new QPushButton(fa::LOCK);
    this->btnDecrypt        = new QPushButton(fa::UNLOCK);
    this->btnLoadFile       = new QPushButton(fa::FILE_UPLOAD);
    this->btnSaveFile       = new QPushButton(fa::FILE_DOWNLOAD);

    connect(this->btnEncrypt, SIGNAL(clicked()), this, SLOT(encrypt()));
    connect(this->btnDecrypt, SIGNAL(clicked()), this, SLOT(decrypt()));
    connect(this->btnLoadFile, SIGNAL(clicked()), this, SLOT(loadFile()));
    connect(this->btnSaveFile, SIGNAL(clicked()), this, SLOT(saveFile()));

    this->btnEncrypt->setToolTip("Encrypt");
    this->btnDecrypt->setToolTip("Decrypt");
    this->btnLoadFile->setToolTip("Load from file");
    this->btnSaveFile->setToolTip("Save to file");

    gridLayout->addWidget(this->txtInputText, 0, 0);
    gridLayout->addWidget(this->btnEncrypt, 0, 1);
    gridLayout->addWidget(this->txtEncryptedText, 0, 2);
    gridLayout->addWidget(this->btnDecrypt, 0, 3);
    gridLayout->addWidget(this->txtDecryptedText, 0, 4);
    gridLayout->addWidget(this->btnLoadFile, 1, 0, Qt::AlignHCenter);
    gridLayout->addWidget(this->btnSaveFile, 1, 4, Qt::AlignHCenter);
    box->setLayout(gridLayout);
    this->gridMainWrapper->addWidget(box, 1, 0);
}

void MainWindow::buildExtras(){
    QGroupBox   *box     = new QGroupBox;
    QHBoxLayout *hLayout = new QHBoxLayout;
    this->progressBar    = new QProgressBar;

    this->progressBar->setTextVisible(false);
    this->progressBar->setToolTip("Progress");

    hLayout->addWidget(this->progressBar);
    box->setLayout(hLayout);
    this->gridMainWrapper->addWidget(box, 2, 0);
}
