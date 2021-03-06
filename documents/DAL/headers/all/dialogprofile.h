#ifndef DIALOGPROFILE_H
#define DIALOGPROFILE_H

#include <QDialog>
#include "../mainwindow.h"
#include <QAbstractButton>

namespace Ui {
class DialogProfile;
}

class DialogProfile : public QDialog
{
    Q_OBJECT

public:
    explicit DialogProfile(Configuration* config, Launcher* launcher);
    ~DialogProfile();
    void refreshTableWidget();
    Configuration* getConfig() const;

signals:
    void selectProfile(unsigned id);

public slots:
    void loadSelectProfile();
    void deleteSelectProfile();
    void setDefaultSelectProfile();
    void enableAtionButton();
    void showDialogCreateProfile();
    void showDialogEditProfile();

private:
    Ui::DialogProfile *ui;
    Configuration* m_conf;
    Launcher* m_launcher;
    QAbstractButton* m_loadButton;
    QAbstractButton* m_createButton;
    QAbstractButton* m_editButton;
    QAbstractButton* m_setDefaultButton;
    QAbstractButton* m_deleteButton;

    void createAndPlaceWidget();
};

#endif // DIALOGPROFILE_H
