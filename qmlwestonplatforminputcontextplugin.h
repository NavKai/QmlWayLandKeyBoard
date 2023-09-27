#ifndef QmlWestonPLATFORMINPUTCONTEXTPLUGIN_H
#define QmlWestonPLATFORMINPUTCONTEXTPLUGIN_H

#include <qpa/qplatforminputcontextplugin_p.h>
#include "qmlwestonplatforminputcontext.h"

class QmlWestonPlatformInputContextPlugin : public QPlatformInputContextPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QPlatformInputContextFactoryInterface_iid FILE "./res/qmlweston.json")

public:
    QmlWestonPlatformInputContext *create(const QString &key, const QStringList &paramlist);
};

#endif // QmlWestonPLATFORMINPUTCONTEXTPLUGIN_H
