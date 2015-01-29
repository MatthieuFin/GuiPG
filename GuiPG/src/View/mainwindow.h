#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../Profile/profile.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(const Profile* p);
        ~MainWindow();

    public slots:
        void setGpgCommandsVisible(bool b);

    private:
        Ui::MainWindow* ui;

};

#endif // MAINWINDOW_H