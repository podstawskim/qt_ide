#include "linenumbers.h"
#include <QDebug>
#include <QPainter>
#include <algorithm>
#include <cmath>

LineNumbers::LineNumbers(QQuickPaintedItem *parent) : QQuickPaintedItem(parent)
{

}

int LineNumbers::lineCount() const {
    return m_lineCount;
}

int LineNumbers::scrollY() const {
    return m_scrollY;
}

void LineNumbers::setLineCount(int lineCount) {
    if(this->m_lineCount == lineCount)
        return;

    this->m_lineCount = lineCount;
    emit lineCountChanged(lineCount);
}

void LineNumbers::setScrollY(int scrollY) {
    if(this->m_scrollY == scrollY)
        return;

    this->m_scrollY = scrollY;
    emit scrollYChanged(scrollY);
}

void LineNumbers::setLineHeight(float lineHeight) {
    if(this->m_lineHeight == lineHeight)
        return;

    this->m_lineHeight = lineHeight;
    emit lineHeightChanged(lineHeight);
}

void LineNumbers::setText(QString text) {
    if(this->m_text == text)
        return;

    this->m_text = text;
    emit textChanged(text);
}

void LineNumbers::setCursorPosition(int cursorPosition) {
    if(this->m_cursorPosition == cursorPosition)
        return;
    this->m_cursorPosition = cursorPosition;
    emit cursorPositionChanged(cursorPosition);

}

void LineNumbers::setSelectionStart(int selectionStart) {
    if(this->m_selectionStart == selectionStart)
        return;
    m_selectionStart = selectionStart;
    emit selectionStartChanged(selectionStart);
}

void LineNumbers::setSelectionEnd(int selectionEnd) {
    if(this->m_selectionEnd == selectionEnd)
        return;
    m_selectionEnd = selectionEnd;
    emit selectionEndChanged(selectionEnd);
}

void LineNumbers::paint(QPainter *painter) {
    //Finding current line
    QString untilSelectedText = this->m_text.mid(0, this->selectionStart());
    int selectedTextStartLine = untilSelectedText.count(QRegExp("[\r\n]"))+1;

    QString selectedText = this->m_text.mid(selectionStart(), (selectionEnd()-selectionStart()));
    int numLinesSelected = selectedText.count(QRegExp("[\r\n]"))+1;

    QString textUntilCursorPosition = m_text.mid(0, m_cursorPosition);
    int cursorLine = textUntilCursorPosition.count(QRegExp("[\r\n]"))+1;

    int firstLineVisible = this->m_scrollY / this->m_lineHeight;
    int lineHeight = int(round(this->m_lineHeight));
    int rest = (m_scrollY>0) ? (m_scrollY % lineHeight) : 0;

    int lastVisibleLine = std::min(firstLineVisible+int(height() / m_lineHeight)+1, m_lineCount);
    int numLines= lastVisibleLine - firstLineVisible;

    for(int i=0; i<numLines; i++) {
        int lineNumber = i+firstLineVisible+1;
        QFont font("times", 24); //--------------------------------
        QFontMetrics fm(font);
        QString text = QString("%1").arg(lineNumber);
        int textWidth = fm.width(text);
        int textHeight = this->m_lineHeight;
        float x= width() - textWidth*0.5 -5;
        float y= 5+i*m_lineHeight - rest;
        QRectF textRect(x, y, textWidth, textHeight);

        if(lineNumber >= selectedTextStartLine && lineNumber < selectedTextStartLine+numLinesSelected) {
            QRectF selecetedTextRect(0, y, width(), textHeight);
            painter->setPen(Qt::yellow);
            painter->drawRect(selecetedTextRect);
            painter->fillRect(selecetedTextRect, Qt::yellow);

        }

        if(lineNumber == cursorLine) {
            QRectF selecetedTextRect(0, y, width(), textHeight);
            painter->setPen(Qt::yellow);
            painter->drawRect(selecetedTextRect);
            painter->fillRect(selecetedTextRect, Qt::yellow);
        }

        painter->setPen(Qt::black);
        painter->drawText(textRect, text);

    }



}

QString LineNumbers::text() const
{
    return m_text;
}

int LineNumbers::cursorPosition() const
{
    return m_cursorPosition;
}

int LineNumbers::selectionStart() const
{
    return m_selectionStart;
}

int LineNumbers::selectionEnd() const
{
    return m_selectionEnd;
}

float LineNumbers::lineHeight() const
{
    return m_lineHeight;
}
