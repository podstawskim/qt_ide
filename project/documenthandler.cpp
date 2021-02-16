#include "documenthandler.h"

 #include <QtGui/QTextDocument>
 #include <QtGui/QTextCursor>
 #include <QtGui/QFontDatabase>
 #include <QtCore/QFileInfo>
 #include <QTextStream>

 QTextStream out(stdout);
 DocumentHandler::DocumentHandler()
     :  m_doc(0),
       m_documentTitle("untitled")
 {
 }

 void DocumentHandler::setFileUrl(const QUrl &arg)
 {
     if (m_fileUrl != arg) {
         m_fileUrl = arg;
         QString fileName = QQmlFile::urlToLocalFileOrQrc(arg);
         if (QFile::exists(fileName)) {
             QFile file(fileName);
             if (file.open(QFile::ReadOnly)) {
                 QByteArray data = file.readAll();
                 QTextCodec *codec = QTextCodec::codecForHtml(data);
                 setText(codec->toUnicode(data));
                 if (m_doc)
                     m_doc->setModified(false);
                 if (fileName.isEmpty())
                     m_documentTitle = QStringLiteral("untitled.txt");
                 else
                     m_documentTitle = QFileInfo(fileName).fileName();

                 emit textChanged();
                 emit documentTitleChanged();
             }
         }
         emit fileUrlChanged();
     }
 }

 QString DocumentHandler::documentTitle() const
   {
       return m_documentTitle;
   }

 void DocumentHandler::setDocumentTitle(QString arg)
   {
       if (m_documentTitle != arg) {
           m_documentTitle = arg;
           emit documentTitleChanged();
       }
   }

 void DocumentHandler::setText(const QString &arg)
 {
     if (m_text != arg) {
         m_text = arg;
         emit textChanged();
     }
 }


 void DocumentHandler::saveAs(const QUrl &arg)
 {
     QString localPath = arg.toLocalFile();
     QFile f(localPath);
     if (!f.open(QFile::WriteOnly | QFile::Truncate)) {
         emit error(tr("Cannot save: ") + f.errorString());
         return;
     }
     QTextStream out(&f);
     out << this->m_text <<endl;
     f.close();
     setFileUrl(QUrl::fromLocalFile(localPath));
 }

 QUrl DocumentHandler::fileUrl() const
 {
     return m_fileUrl;
 }

 QString DocumentHandler::text() const
 {
     return m_text;
 }




