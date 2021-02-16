#ifndef TEXTFORMAT_H
#define TEXTFORMAT_H


#include <QObject>
#include <QTextCharFormat>

class TextFormat : public QObject, public QTextCharFormat
{
    Q_OBJECT
    Q_PROPERTY (QVariant textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)

public:
    TextFormat(QObject* parent = nullptr);

signals:
    void textColorChanged();

protected:
    QVariant textColor() const;
    void setTextColor(const QVariant& textColor);

};


#endif // TEXTFORMAT_H
