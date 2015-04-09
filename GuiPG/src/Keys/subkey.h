#ifndef SUBKEY_H
#define SUBKEY_H

#include "key.h"
#include "signature.h"

class SubKey : public Key {
    Q_OBJECT

    public:
        SubKey();
        ~SubKey();

        const QList<Signature*> getSignatures() const;
        void addSignature(Signature* sig);

    private:
        QList<Signature*> m_sigs;
};

#endif // SUBKEY_H
