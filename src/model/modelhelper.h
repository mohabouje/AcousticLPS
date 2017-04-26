#ifndef MODELHELPER_H
#define MODELHELPER_H

#include <QString>
#include <QStandardPaths>
#include <QDir>

namespace ModelHelper {
    inline QString defaultDocumentsFolder() {
        static const QString path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/AcousticLPS/";
        QDir dir(path);
        if (!dir.exists()) {
            dir.mkdir(path);
        }
        return path;
    }


}
#endif // MODELHELPER_H
