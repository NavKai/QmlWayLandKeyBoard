#ifndef QmlWestonPLATFORMINPUTCONTEXT_H
#define QmlWestonPLATFORMINPUTCONTEXT_H

#include <qpa/qplatforminputcontext.h>
#include <QtQuickWidgets/QQuickWidget>
#include <QQuickView>

#include <QQmlComponent>

class QmlWestonPlatformInputContext : public QPlatformInputContext
{
    Q_OBJECT
public:
    QmlWestonPlatformInputContext();
    ~QmlWestonPlatformInputContext();

    bool isValid() const Q_DECL_OVERRIDE;
    void setFocusObject(QObject *object) Q_DECL_OVERRIDE;
    void showInputPanel() Q_DECL_OVERRIDE;
    void hideInputPanel() Q_DECL_OVERRIDE;
    bool isInputPanelVisible() const Q_DECL_OVERRIDE;

public slots:
    void sendKeyToFocusItem(const QString &keytext);
    void hideKeyBoard();

private:
    QObject *m_focusitem;

    QQmlComponent* m_keyBoardCom{nullptr};
    QQuickItem* m_keyBoardItem{nullptr};
};

#endif // QmlWestonPLATFORMINPUTCONTEXT_H
