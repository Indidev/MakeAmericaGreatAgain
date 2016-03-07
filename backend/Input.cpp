#include "Input.h"

QStringList Input::loadLines(QString filepath)
{
    QStringList list;

    QFile file(filepath);
    if (file.exists()) {
        file.open(QIODevice::ReadOnly | QIODevice::Text);

        QTextStream stream(&file);
        while (!stream.atEnd()) {
            list.append(stream.readLine());
        }
    }

    return list;
}

