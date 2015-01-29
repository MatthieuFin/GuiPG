#include "profile.h"

Profile::Profile(unsigned id, const QString& name) : m_id(id), m_name(name) {

}

unsigned Profile::getId() const {
    return m_id;
}

const QString& Profile::getName() const {
    return m_name;
}

const QString& Profile::getGPGExecutable() const {
    return m_exec;
}

void Profile::setGPGExecutable(const QString& exec) {
    m_exec = exec;
}

const QString& Profile::getConfigurationPath() const {
    return m_path;
}

void Profile::setConfigurationPath(const QString& path) {
    m_path = path;
}