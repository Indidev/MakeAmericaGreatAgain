#include "ResourceProvider.h"
ResourceProvider* ResourceProvider::self = NULL;

ResourceProvider::ResourceProvider(QString resourceList)
{
    QStringList lines = Input::loadLines(resourceList);

    bool images = true;

    for (QString line : lines) {
        if (line.trimmed().toLower() == "questions")
            images = false;

        int index = line.indexOf(':');
        if (index >= 0) {
            QString key = line.left(index++).trimmed();
            QString path = line.right(line.size() - index).trimmed();

            if (images) {
                imageMap[key] = new QImage(path);
            } else { //load question file
                questions[key] = Input::loadLines(path);
            }
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

QList<QString> ResourceProvider::qPack(QString key)
{
    if (!self || !self->questions.contains(key))
        return QList<QString>();

    return self->questions[key];
}

QList<QString> ResourceProvider::qKeys()
{
    if (!self)
        return QList<QString>();

    return self->questions.keys();
}
