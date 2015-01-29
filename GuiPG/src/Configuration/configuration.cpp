#include "configuration.h"
#include <QFile>
#include <QDomDocument>
#include <QTextStream>
#include <iostream>

#ifdef _WIN32
#define DEF_GPG_EXEC "C:/Program Files (x86)/GNU/GnuPG/gpg2.exe"
#else
#define DEF_GPG_EXEC "gpg"
#endif

#define EXEC_TAG_NAME "exec"
#define GPG_TAG_NAME "gpg"
#define ID_ATTR_NAME "id"
#define NAME_ATTR_NAME "name"
#define PROFILE_TAG_NAME "profile"
#define ROOT_TAG_NAME "configurations"
#define VALUE_ATTR_NAME "value"

using namespace std;

Configuration::Configuration(const QString& filePath)
    : m_currentProfile(nullptr), m_filePath(filePath) {
    QFile f(m_filePath);
    if (!f.open(QIODevice::ReadOnly)) {
        cerr << "Unable to open '" << m_filePath.toStdString() << "'" << endl;
        initConfig();
    } else if (!m_doc.setContent(&f)) {
        f.close();
        cerr << "'" << m_filePath.toStdString() << "' is an invalid XML file"
             << endl;
        initConfig();
    }
}

bool Configuration::isLoaded() const {
    return m_currentProfile != nullptr;
}

bool Configuration::loadProfiles() {
    QDomElement root = m_doc.documentElement();
    if (root.tagName() != ROOT_TAG_NAME) {
        return false;
    }
    QDomElement e = root.firstChildElement(PROFILE_TAG_NAME);
    while (!e.isNull()) {
        bool ok = false;
        unsigned id = e.attribute(ID_ATTR_NAME).toUInt(&ok);
        if (ok) {
            Profile* p = new Profile(id, e.attribute(NAME_ATTR_NAME));
            m_profiles.append(p);
        }
        e = e.nextSiblingElement(PROFILE_TAG_NAME);
    }
    return true;
}

bool Configuration::loadVars(const Profile* p) {
    m_currentProfile = p;
    m_vars.clear();

    QDomElement root = m_doc.documentElement();
    if (root.tagName() != ROOT_TAG_NAME) {
        return false;
    }
    QDomElement e = root.firstChildElement(PROFILE_TAG_NAME);
    while (!e.isNull()
           && !attrIsProfileId(e.attribute(ID_ATTR_NAME), p->getId())) {
        e = e.nextSiblingElement(PROFILE_TAG_NAME);
    }
    if (!e.isNull()) {
        m_profileElement = e;
        loadConfig(e.firstChild());
    }
    return true;
}

const Profile* Configuration::getCurrentProfile() const {
    return m_currentProfile;
}

const QList<Profile*>& Configuration::getProfiles() const {
    return m_profiles;
}

const QHash<QString, QDomElement>& Configuration::getVars() const {
    return m_vars;
}

bool Configuration::save() {
    QFile f(m_filePath);
    if (!f.open(QIODevice::WriteOnly)) {
        return false;
    }
    QTextStream out(&f);
    out << m_doc.toString();
    f.close();
    return true;
}

bool Configuration::attrIsProfileId(const QString& attr, unsigned id) const {
    bool ok = false;
    unsigned x = attr.toUInt(&ok);
    return ok && x == id;
}

void Configuration::initConfig() {
    QDomElement root = m_doc.createElement(ROOT_TAG_NAME);
    m_profileElement = m_doc.createElement(PROFILE_TAG_NAME);
    m_profileElement.setAttribute(ID_ATTR_NAME, m_currentProfile->getId());
    m_doc.appendChild(root);
    root.appendChild(m_profileElement);
}

void Configuration::loadConfig(QDomNode root, const QString& parent) {
    while (!root.isNull()) {
        if (root.isElement()) {
            QDomElement e = root.toElement();
            if (e.hasAttribute(VALUE_ATTR_NAME)) {
                m_vars.insert(parent + e.tagName(), e);
            }
            loadConfig(e.firstChild(), parent + e.tagName() + "/");
        }
        root = root.nextSibling();
    }
}
