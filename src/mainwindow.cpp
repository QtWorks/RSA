#include "mainwindow.h"
#include "ui_mainwindow.h"

void test(){
    auto blub = std::make_shared<vector<int64>>();
    blub->push_back(1);
    blub->push_back(2);
    blub->push_back(5);
    blub->push_back(5);
    auto t = rsa::generatePairs(blub);
    for (auto i : *t){
        qWarning() << i;
    }
}

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
    test();
}

MainWindow::~MainWindow(){
}

void MainWindow::encrypt(){
    QString  encryptedText {};
    rsa::Key publicKey     {this->publicE->text().toInt(),
                            0,
                            this->publicN->text().toInt()};

    auto inputText = std::make_shared<string>(this->txtInputText->toPlainText().toStdString());
    auto numbers   = rsa::encode(publicKey, inputText);

    for (const auto & number : *numbers){
        encryptedText += QString::number(number) + " ";
    }

    this->txtEncryptedText->setText(encryptedText);
}

void MainWindow::decrypt(){
    rsa::Key publicKey {0,
                        this->privateD->text().toInt(),
                        this->privateN->text().toInt()};
    auto numbers = std::make_shared<vector<int64>>();

    for (const auto &number : this->txtEncryptedText->toPlainText().split(" ")){
        numbers->push_back(number.toLongLong());
    }

    this->txtDecryptedText->setText(QString::fromStdString(*rsa::decode(publicKey, numbers)));
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

void MainWindow::showKeyGenerationDialog(){
    KeyGenerationDialog dialog{this};
    this->setWindowOpacity(0.7);
    dialog.exec();
    this->setWindowOpacity(1);
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
    QGroupBox   *box                = new QGroupBox;
    QGridLayout *gridLayout         = new QGridLayout;
    QLabel      *labelPublicE       = new QLabel("Public E:");
    QLabel      *labelPublicN       = new QLabel("Public N:");
    QLabel      *labelPrivateD      = new QLabel("Private D:");
    QLabel      *labelPrivateN      = new QLabel("Private N:");
    this->publicE                   = new QLineEdit("1721");
    this->publicN                   = new QLineEdit("263713");
    this->privateD                  = new QLineEdit("1373");
    this->privateN                  = new QLineEdit("263713");
    this->btnShowKeyGenerationPanel = new QPushButton(fa::KEY);

    this->btnShowKeyGenerationPanel->setToolTip("Show key generation panel");
    connect(this->btnShowKeyGenerationPanel, SIGNAL(clicked()), this, SLOT(showKeyGenerationDialog()));

    gridLayout->addWidget(labelPublicE, 0, 0);
    gridLayout->addWidget(this->publicE, 0, 1);
    gridLayout->addWidget(labelPublicN, 0, 2);
    gridLayout->addWidget(this->publicN, 0, 3);
    gridLayout->addWidget(labelPrivateD, 1, 0);
    gridLayout->addWidget(this->privateD, 1, 1);
    gridLayout->addWidget(labelPrivateN, 1, 2);
    gridLayout->addWidget(this->privateN, 1, 3);
    gridLayout->addWidget(this->btnShowKeyGenerationPanel, 0, 4, 2, 1);
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

    this->txtInputText->setAcceptRichText(false);
    this->txtEncryptedText->setAcceptRichText(false);
    this->txtDecryptedText->setAcceptRichText(false);

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
