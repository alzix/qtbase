// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

//! [0]
class Employee
{
public:
    Employee() {}
    Employee(const Employee &other);

    Employee &operator=(const Employee &other);

private:
    QString myName;
    QDate myDateOfBirth;
};
//! [0]


//! [1]
QList<QString> list;
list << "A" << "B" << "C" << "D";

QListIterator<QString> i(list);
while (i.hasNext())
    QString s = i.next();
//! [1]


//! [2]
QListIterator<QString> i(list);
i.toBack();
while (i.hasPrevious())
    QString s = i.previous();
//! [2]


//! [3]
QMutableListIterator<int> i(list);
while (i.hasNext()) {
    if (i.next() % 2 != 0)
        i.remove();
}
//! [3]


//! [4]
QMutableListIterator<int> i(list);
i.toBack();
while (i.hasPrevious()) {
    if (i.previous() % 2 != 0)
        i.remove();
}
//! [4]


//! [5]
QMutableListIterator<int> i(list);
while (i.hasNext()) {
    if (i.next() > 128)
        i.setValue(128);
}
//! [5]


//! [6]
QMutableListIterator<int> i(list);
while (i.hasNext())
    i.next() *= 2;
//! [6]


//! [7]
QMap<QString, QString> map;
map.insert("Paris", "France");
map.insert("Guatemala City", "Guatemala");
map.insert("Mexico City", "Mexico");
map.insert("Moscow", "Russia");
...

QMutableMapIterator<QString, QString> i(map);
while (i.hasNext()) {
    if (i.next().key().endsWith("City"))
        i.remove();
}
//! [7]


//! [8]
QMap<int, QWidget *> map;
QHash<int, QWidget *> hash;

QMapIterator<int, QWidget *> i(map);
while (i.hasNext()) {
    i.next();
    hash.insert(i.key(), i.value());
}
//! [8]


//! [9]
QMutableMapIterator<int, QWidget *> i(map);
while (i.findNext(widget))
    i.remove();
//! [9]


//! [10]
QList<QString> list;
list << "A" << "B" << "C" << "D";

QList<QString>::iterator i;
for (i = list.begin(); i != list.end(); ++i)
    *i = (*i).toLower();
//! [10]


//! [11]
QList<QString> list;
list << "A" << "B" << "C" << "D";

QList<QString>::reverse_iterator i;
for (i = list.rbegin(); i != list.rend(); ++i)
    *i = i->toLower();
//! [11]


//! [12]
QList<QString>::const_iterator i;
for (i = list.constBegin(); i != list.constEnd(); ++i)
    qDebug() << *i;
//! [12]


//! [13]
QMap<int, int> map;
...
QMap<int, int>::const_iterator i;
for (i = map.constBegin(); i != map.constEnd(); ++i)
    qDebug() << i.key() << ':' << i.value();
//! [13]


//! [14]
// RIGHT
const QList<int> sizes = splitter->sizes();
QList<int>::const_iterator i;
for (i = sizes.begin(); i != sizes.end(); ++i)
    ...

// WRONG
QList<int>::const_iterator i;
for (i = splitter->sizes().begin();
        i != splitter->sizes().end(); ++i)
    ...
//! [14]


//! [15]
QList<QString> values;
...
QString str;
foreach (str, values)
    qDebug() << str;
//! [15]


//! [16]
QList<QString> values;
...
QListIterator<QString> i(values);
while (i.hasNext()) {
    QString s = i.next();
    qDebug() << s;
}
//! [16]


//! [17]
QList<QString> values;
...
foreach (const QString &str, values)
    qDebug() << str;
//! [17]


//! [18]
QList<QString> values;
...
foreach (const QString &str, values) {
    if (str.isEmpty())
        break;
    qDebug() << str;
}
//! [18]


//! [19]
QMap<QString, int> map;
...
foreach (const QString &str, map.keys())
    qDebug() << str << ':' << map.value(str);
//! [19]


//! [20]
QMultiMap<QString, int> map;
...
foreach (const QString &str, map.uniqueKeys()) {
    foreach (int i, map.values(str))
        qDebug() << str << ':' << i;
}
//! [20]


//! [21]
forever {
    ...
}
//! [21]


//! [22]
CONFIG += no_keywords
//! [22]


//! [cmake_no_keywords]
target_compile_definitions(my_app PRIVATE QT_NO_KEYWORDS)
//! [cmake_no_keywords]


//! [23]
QString onlyLetters(const QString &in)
{
    QString out;
    for (int j = 0; j < in.size(); ++j) {
        if (in[j].isLetter())
            out += in[j];
    }
    return out;
}
//! [23]

//! [24]
QList<int> a, b;
a.resize(100000); // make a big list filled with 0.

QList<int>::iterator i = a.begin();
// WRONG way of using the iterator i:
b = a;
/*
    Now we should be careful with iterator i since it will point to shared data
    If we do *i = 4 then we would change the shared instance (both vectors)
    The behavior differs from STL containers. Avoid doing such things in Qt.
*/

a[0] = 5;
/*
    Container a is now detached from the shared data,
    and even though i was an iterator from the container a, it now works as an iterator in b.
    Here the situation is that (*i) == 0.
*/

b.clear(); // Now the iterator i is completely invalid.

int j = *i; // Undefined behavior!
/*
    The data from b (which i pointed to) is gone.
    This would be well-defined with STL containers (and (*i) == 5),
    but with QList this is likely to crash.
*/
//! [24]

//! [25]
QList<int> list { 1, 2, 3, 4, 4, 5 };
QSet<int> set(list.begin(), list.end());
/*
    Will generate a QSet containing 1, 2, 3, 4, 5.
*/
//! [25]

//! [26]
QList<int> list { 2, 3, 1 };

std::sort(list.begin(), list.end());
/*
    Sort the list, now contains { 1, 2, 3 }
*/

std::reverse(list.begin(), list.end());
/*
    Reverse the list, now contains { 3, 2, 1 }
*/

int even_elements =
        std::count_if(list.begin(), list.end(), [](int element) { return (element % 2 == 0); });
/*
    Count how many elements that are even numbers, 1
*/

//! [26]
