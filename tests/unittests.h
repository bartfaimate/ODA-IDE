#ifndef UNITTESTS_H
#define UNITTESTS_H

#include <QObject>
#include <QtTest/QTest>
#include "../settings.h"

class UnitTests : public QObject
{
    Q_OBJECT
public:
    explicit UnitTests(QObject *parent = nullptr);

signals:

public slots:
    void test_saveSettings();
    void test_loadSettings();
};




UnitTests::UnitTests(QObject *parent) : QObject(parent)
{
    QMap<QString, QVariant> data;
    data["foo"] = 42;
    bool success = Settings::saveSettings("test/test.ini", data);
    QVERIFY(success == true);
}

void UnitTests::test_saveSettings()
{

}

QTEST_MAIN(UnitTests)
#include "unittests.moc"
#endif // UNITTESTS_H
