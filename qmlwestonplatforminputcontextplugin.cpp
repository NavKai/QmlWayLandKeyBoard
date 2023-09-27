#include "qmlwestonplatforminputcontextplugin.h"

QmlWestonPlatformInputContext * QmlWestonPlatformInputContextPlugin::create(const QString &key, const QStringList &paramlist)
{
    Q_UNUSED(paramlist)

    if(key.compare("qmlweston",Qt::CaseInsensitive) == 0)
    {
        return new QmlWestonPlatformInputContext;
    }
    return nullptr;
}
