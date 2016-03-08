#ifndef RESOURCEPROVIDER_H
#define RESOURCEPROVIDER_H

#include <QMap>
#include <QImage>
#include <QString>
#include <QStringList>
#include <QDebug>

#include "backend/Input.h"

class ResourceProvider
{
public:
    ResourceProvider(QString resourceList);
    ~ResourceProvider();
    static const ResourceProvider* instance() {return self;}
    static QImage* img(const QString &key);
    static QList<QString> qPack(QString key);
    static QList<QString> qKeys();

private:
    QMap<QString, QImage*> imageMap;
    QMap<QString, QList<QString>> questions;
    static ResourceProvider *self;
};

#endif // RESOURCEPROVIDER_H
