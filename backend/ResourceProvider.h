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

private:
    QMap<QString, QImage*> imageMap;
    static ResourceProvider *self;
};

#endif // RESOURCEPROVIDER_H
