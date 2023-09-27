#include "qmlwestonplatforminputcontext.h"

#include <QKeyEvent>
#include <QApplication>

#include <QDebug>
#include <QQuickItem>
#include <QQmlEngine>
#include <QQmlContext>

#include <QScreen>

#include <QGuiApplication>
#include <QApplication>

#include <QWindow>
#include <QQmlApplicationEngine>

QmlWestonPlatformInputContext::QmlWestonPlatformInputContext()
{
}

QmlWestonPlatformInputContext::~QmlWestonPlatformInputContext()
{

}

void QmlWestonPlatformInputContext::sendKeyToFocusItem(const QString &keytext)
{
    if(!m_focusitem)return;

    if(keytext == QString("\x7F"))     //Backspace <--
    {
        QCoreApplication::sendEvent(m_focusitem, new QKeyEvent(QEvent::KeyPress, Qt::Key_Backspace, Qt::NoModifier));
        QCoreApplication::sendEvent(m_focusitem, new QKeyEvent(QEvent::KeyRelease, Qt::Key_Backspace, Qt::NoModifier));
    }
    else if(keytext == QString("\n"))
    {
        QCoreApplication::sendEvent(m_focusitem, new QKeyEvent(QEvent::KeyPress, Qt::Key_Return, Qt::NoModifier));
        QCoreApplication::sendEvent(m_focusitem, new QKeyEvent(QEvent::KeyRelease, Qt::Key_Return, Qt::NoModifier));
    }
    else if(keytext == QString("&&"))
    {
        QCoreApplication::sendEvent(m_focusitem, new QKeyEvent(QEvent::KeyPress, 0, Qt::NoModifier,"&"));
        QCoreApplication::sendEvent(m_focusitem, new QKeyEvent(QEvent::KeyRelease, 0, Qt::NoModifier,"&"));
    }
    else if(keytext == QString("back"))     //Backspace <--
    {
        QCoreApplication::sendEvent(m_focusitem, new QKeyEvent(QEvent::KeyPress, Qt::Key_Backspace, Qt::NoModifier));
        QCoreApplication::sendEvent(m_focusitem, new QKeyEvent(QEvent::KeyRelease, Qt::Key_Backspace, Qt::NoModifier));
    }
    else if(keytext == QString("ok"))
    {
        QCoreApplication::sendEvent(m_focusitem, new QKeyEvent(QEvent::KeyPress, Qt::Key_Enter, Qt::NoModifier));
        QCoreApplication::sendEvent(m_focusitem, new QKeyEvent(QEvent::KeyRelease, Qt::Key_Enter, Qt::NoModifier));
    }
    else
    {
        QCoreApplication::sendEvent(m_focusitem, new QKeyEvent(QEvent::KeyPress, 0, Qt::NoModifier, keytext));
        QCoreApplication::sendEvent(m_focusitem, new QKeyEvent(QEvent::KeyRelease, 0, Qt::NoModifier, keytext));
    }
}

void QmlWestonPlatformInputContext::hideKeyBoard()
{
    hideInputPanel();
}

bool QmlWestonPlatformInputContext::isValid() const
{
    return true;
}

void QmlWestonPlatformInputContext::setFocusObject(QObject *object)
{
    qDebug() << __FUNCTION__ << object;

    auto focusItem = dynamic_cast<QQuickItem*>(object);
    if (!focusItem)
    {
        return;
    }
    bool AcceptsInput = focusItem->inputMethodQuery(Qt::ImEnabled).toBool();
    if (!AcceptsInput)
    {
        hideInputPanel();
        return;
    }
    m_focusitem = object;
}

void QmlWestonPlatformInputContext::showInputPanel()
{
    qDebug() << __FUNCTION__;
    if(!m_keyBoardCom){
        auto engin = (QQmlApplicationEngine *)(qApp->property("engine").value<QObject*>());
        qDebug() << engin->rootContext();
        m_keyBoardCom = new QQmlComponent(engin,QUrl("qrc:/keyboard.qml"));
        engin->rootContext()->setContextProperty("BackEnd",this);
        m_keyBoardItem = qobject_cast<QQuickItem*>(m_keyBoardCom->create());
        QQmlEngine::setObjectOwnership(m_keyBoardItem, QQmlEngine::CppOwnership);

        QQuickWindow *window = qobject_cast<QQuickWindow*>(engin->rootObjects().at(0));
        QQuickItem *root = window->contentItem();

        m_keyBoardItem->setParentItem(root);
        m_keyBoardItem->setParent(engin);
    }
    m_keyBoardItem->setVisible(true);
    emitInputPanelVisibleChanged();
}

void QmlWestonPlatformInputContext::hideInputPanel()
{
    qDebug() << __FUNCTION__;
    if(m_keyBoardItem){
        m_keyBoardItem->setVisible(false);
    }
    emitInputPanelVisibleChanged();
}

bool QmlWestonPlatformInputContext::isInputPanelVisible() const
{
    qDebug() << __FUNCTION__;
    if(!m_keyBoardItem)
        return false;
    return m_keyBoardItem->isVisible();
}

