#include "textformat.h"


TextFormat::TextFormat(QObject* parent) :
    QObject(parent)
{
}


QVariant TextFormat::textColor() const
{
    return QTextFormat::foreground().color();
}

void TextFormat::setTextColor( const QVariant& foreground )
{
    if ( foreground.canConvert<QColor>() )
    {
        QTextCharFormat::setForeground( QBrush( foreground.value< QColor >() ) );
        emit textColorChanged();
    }
}

