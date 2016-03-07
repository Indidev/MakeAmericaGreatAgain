#include "ResourceProvider.h"
ResourceProvider* ResourceProvider::self = NULL;

ResourceProvider::ResourceProvider(QString resourceList)
{
    QStringList lines = Input::loadLines(resourceList);

    for (QString line : lines) {
        int index = line.indexOf(':');
        if (index >= 0) {
            QString key = line.left(index++).trimmed();
            QString imgPath = line.right(line.size() - index).trimmed();

            imageMap[key] = new QImage(imgPath);
        }
    }
    self = this;
}

ResourceProvider::~ResourceProvider()
{
    for (QImage* img: imageMap)
        delete(img);
}

QImage *ResourceProvider::img(const QString &key)
{
    if (!self || !self->imageMap.contains(key))
        return NULL;

    return self->imageMap[key];
}
