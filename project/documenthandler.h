
#ifndef DOCUMENTHANDLER_H
#define DOCUMENTHANDLER_H
#include <qqmlfile.h>
#include <QQuickTextDocument>
#include <QFileSelector>

#include <QtGui/QTextCharFormat>
#include <QtCore/QTextCodec>



class QTextDocument;

class DocumentHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString documentTitle READ documentTitle WRITE setDocumentTitle NOTIFY documentTitleChanged)
    Q_PROPERTY(QUrl fileUrl READ fileUrl WRITE setFileUrl NOTIFY fileUrlChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)


public:
    DocumentHandler();
    QUrl fileUrl() const;
    QString text() const;
    QString documentTitle() const;

public Q_SLOTS:
    void setText(const QString &arg);
    void setFileUrl(const QUrl &arg);
    void saveAs(const QUrl &arg);
    void setDocumentTitle(QString arg);

Q_SIGNALS:
    void targetChanged();
    void fileUrlChanged();
    void textChanged();
    void error(QString message);
    void documentTitleChanged();
private:
    void reset();
    QTextCursor textCursor() const;
    void mergeFormatOnWordOrSelection(const QTextCharFormat &format);
    QTextDocument *m_doc;
    QUrl m_fileUrl;
    QString m_text;
    QString m_documentTitle;
};

#endif
