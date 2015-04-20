#include "keyimport.h"
#include "ui_keyimport.h"
#include "QFileDialog"
#include "QDebug"

KeyImport::KeyImport(MainWindow* parent) :
    QDialog(parent),
    ui(new Ui::KeyImport),
    m_window(parent),
    m_profile(parent->getProfil())
{
    ui->setupUi(this);
}

KeyImport::~KeyImport()
{
    delete ui;
}

void KeyImport::on_cancelButton_clicked()
{
    close();
}

void KeyImport::on_browseButton_clicked()
{
    QString filename=QFileDialog::getOpenFileName(this,tr("Open File"),
        "~","All files (*)" );
    ui->pathEdit->setText(filename);
    ui->fileRadioButton->click();
}

void KeyImport::on_pathEdit_textChanged(const QString &arg1)
{
    if (arg1 == "") {
        // not used.
    }
    ui->fileRadioButton->click();
}

void KeyImport::on_keyIdEdit_textChanged(const QString &arg1)
{
    if (arg1 == "") {
        // not used.
    }
    ui->keyServerButton->click();
}

void KeyImport::on_importButton_clicked()
{
    if (ui->fileRadioButton->isChecked()) {
        Action keyImport(QString("--import"), QStringList() << ui->pathEdit->text(), QStringList() << "--allow-secret-key-import");
        GPGManager* manager = new GPGManager(m_profile);
        connect(manager, &GPGManager::finished, this, &KeyImport::keyImportFinished);
        manager->setAction(keyImport);
        manager->execute();
    } else {
        if (ui->keyServerButton->isChecked()) {
            Action keyImport(QString("--recv-keys"), QStringList() << ui->keyIdEdit->text(), QStringList() << "--keyserver hkp://keys.gnupg.net");
            GPGManager* manager = new GPGManager(m_profile);
            connect(manager, &GPGManager::finished, this, &KeyImport::keyImportFinished);
            manager->setAction(keyImport);
            manager->execute();
            ui->warningLabel->setText("Veuillez patienter pendant l'importation...");
            ui->importButton->setDisabled(true);
        }
    }
}

void KeyImport::keyImportFinished(int a, QString s)
{
    if (a || s == "") {
        // not used.
    }
    m_window->getModel()->getKeyManager()->load();
    close();
}
