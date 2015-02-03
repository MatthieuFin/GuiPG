#ifndef GUIPGAPP_H
#define GUIPGAPP_H

#include <QObject>
#include <QApplication>
#include "../Profile/profile.h"
#include "../Configuration/configuration.h"

class GuiPGApp : public QApplication {

        Q_OBJECT

    public:
        GuiPGApp(int& argc, char** argv);

        ~GuiPGApp();
    signals:
    public slots:
        void launchApp(Profile* p, Configuration* config);
};

#endif // GUIPGAPP_H
