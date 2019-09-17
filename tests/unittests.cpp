#ifndef UNITTESTS_H
#define UNITTESTS_H

#include <QObject>
#include <QtTest/QTest>
#include "../settings.h"
#include <QMap>
#include <QVariant>

class UnitTests : public QObject
{
    Q_OBJECT
public:
 
signals:

private slots:
    void test_saveSettings();
    void test_loadSettings();
};



void UnitTests::test_saveSettings()
{
    QMap<QString, QVariant> data;
    data.insert("foo", 42);
    data.insert("bar/foo", 4242);

    bool success = Settings::saveSettings("./test_foo.ini", data);
    QCOMPARE(success, true);
}

void UnitTests::test_loadSettings()
{
    QMap<QString, QVariant> data;
    bool success = Settings::loadSettings("./test_foo.ini", data);
    QCOMPARE(success, true);
    int foo = data.value("foo").toInt();
    QCOMPARE(foo, 42);
    
    int foobar = data.value("bar/foo").toInt();
    QCOMPARE(foobar, 4242);

}

QTEST_MAIN(UnitTests)
#include "unittests.moc"

#endif
