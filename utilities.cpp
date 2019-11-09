#include "utilities.h"

#include <QFileInfo>

Utilities::Utilities()
{

}

bool Utilities::existsDirecotry(const QString dirPath)
{

    const QFileInfo outputDir(dirPath);
   if ((!outputDir.exists()) || (!outputDir.isDir()) || (!outputDir.isWritable())) {
        return false;
   }
   else {
       return true;
   }
}
