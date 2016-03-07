#ifndef INPUT_H
#define INPUT_H

#include <QHash>
#include <QString>
#include <QFile>
#include <QTextStream>


/**
 * @brief The Input class
 * class which contains functions to read from files
 */
class Input
{
public:
    /**
     * load all lines of a file
     * @param filepath path of the file...
     * @return content of file as list
     */
    static QStringList loadLines(QString filepath);

private:
    Input(){}
};

#endif // INPUT_H
