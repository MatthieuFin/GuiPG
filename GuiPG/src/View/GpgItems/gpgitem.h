#ifndef GPGITEM_H
#define GPGITEM_H

#include <QObject>
#include <QTreeWidgetItem>
#include "../../Keys/gpgobject.h"
#include <QPoint>
#include "../../Configuration/configuration.h"
#include "../../GPG/gpgmanager.h"

// X(nom de l'enum, nom de la colone)
#define X_COLUMNS               \
X(COL_NAME,       "Nom")        \
X(COL_MAIL,       "Email")      \
X(COL_VALIDITY,   "Validité")   \
X(COL_TRUST,      "Confiance")  \
X(COL_CREATION,   "Création")   \
X(COL_EXPIRATION, "Expiration") \
X(COL_LENGTH,     "Taille")     \
X(COL_ALGO,       "Algo")       \
X(COL_CAPACITY,   "Capacité")   \
X(COL_ID,         "ID")


class GpgItem :  public QObject, public QTreeWidgetItem {
        Q_OBJECT
    public:

        GpgItem(QTreeWidget * parent, GpgObject* gpgObject);
        GpgItem(GpgObject* gpgObject);
        virtual ~GpgItem() = 0;

        virtual void showMenu(const QPoint &pos) = 0;

        // Cette enum permet de conter le nombre de colones
        // définie et de leur attribuer un numéro selon leur ordre de définition.
        #define X(id, str) id,
        enum columnsNumber {
            X_COLUMNS
            NB_COLUMNS
        };
        #undef X

        static QHash<int, QString> columns;

        QString getFpr();

    public slots:
        void changed(int s, QString output);

    private slots:
        void onGpgUpdate(int s, QString output);

    protected:
        GpgObject* m_gpgObject;
        GPGManager* m_gpg;
        QMenu* m_menu;
        QPoint m_pos;
        QString m_fpr;
};

#endif // GPGITEM_H
