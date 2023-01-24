#ifndef UTIL_H
#define UTIL_H

#include <QString>
#include <QTextCodec>
#include <QTextEncoder>

QString cp1251_to_utf(char *text)
{
    return QTextCodec::codecForName("Windows-1251")->toUnicode(text);
}

char* utf_to_cp1251(QString text)
{
    QTextEncoder *enc = QTextCodec::codecForName("Windows-1251")->makeEncoder();
    char* result =  enc->fromUnicode(text).data();
    return result;
}
#endif // UTIL_H
