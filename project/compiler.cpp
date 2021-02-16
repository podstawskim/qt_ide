//#include "compiler.h"

//Compiler::Compiler(QObject *parent) : QObject(parent)
//{

//}

//void Compiler::compile(QString outputFile)
//{
//    void Compiler::compile(QString outputFile)
//    {
//    //    QString fileExtension = file.right(file.size()-file.lastIndexOf('.')-1);
//    //    QString args;
//    //    QStringList options;
//    //    options << "cpp" << "c" << "java" << "pro";
//    //    switch(options.indexOf(fileExtension))
//    //    {
//    //        case 0: //cpp
//    //            args = "g++ " + file;
//    //            if(outputFile != NULL)
//    //                args+= " -o " + outputFile;
//    //            break;
//    //        case 1: //c
//    //            args = "gcc " + file;
//    //            if(outputFile != NULL)
//    //                args+= " -o " + outputFile;
//    //            break;
//    //        case 2: //java
//    //            args = "javac " + file;
//    //            break;
//    //        case 3: //pro
//    //            args = "cd ..; mkdir build-prject; cd mkdir-project; /usr/bin/qmake/ ../project; make -j4";
//    //            break;
//    //        default:
//    //            return;
//    //    }
//    //    QProcess process;
//    //    process.setWorkingDirectory(path);
//    //    process.start("sh", QStringList() << "-c" << args);
//    //    if (!process.waitForFinished()) {
//    //           qDebug() << "Failed to execute!!";
//    //           const QString error = process.readAllStandardError();
//    //           if (!error.isEmpty()) {
//    //            qDebug () << "Exit status: " << process.exitStatus() << ", Error: " << error;
//    //           }
//    //            return;
//    //        }
//    //    const QString output = process.readAllStandardOutput();
//    //    qDebug().noquote() <<output;

//        this->setOutput("AAAAAAA");
//    }
//}

//void Compiler::run(QString arguments)
//{
//    QProcess process;
//    process.setWorkingDirectory(path);
//    QString prog = "./" + file;
////    if(arguments != NULL)
////        prog+= " -o " + outputFile;
//    process.start(prog, QStringList() << arguments);
//    if (!process.waitForFinished()) {
//           qDebug() << "Failed to execute!!";
//           const QString error = process.readAllStandardError();
//           if (!error.isEmpty()) {
//            qDebug () << "Exit status: " << process.exitStatus() << ", Error: " << error;
//           }
//            return;
//        }
//    const QString output = process.readAllStandardOutput();
//    comp_output = output;
//    qDebug().noquote() << comp_output;
//    emit changed_output(comp_output);
//    //qDebug().noquote() <<output;
//}

//void Compiler::setFileNameAndPath(QFileSystemModel* fileSystemModel, const QModelIndex &modelIndex)
//{
//    path = fileSystemModel->filePath(modelIndex);
//    file = path.right(path.size()-path.lastIndexOf('/')-1);
//    path = path.left(path.lastIndexOf('/')+1);
//    //qDebug() << "Path/File: " << path <<file;
//}
//QString Compiler::getFileName()
//{
//    return file;
//}
//QString Compiler::getOutput()
//{
//    qDebug().noquote() << comp_output;
//    return comp_output;
//}
//QString Compiler::getFileContent()
//{
//    QProcess process;
//    process.setWorkingDirectory(path);
//    QString prog = "cat " + file;
//    process.start(prog);
//    if (!process.waitForFinished()) {
//           qDebug() << "Failed to execute!!";
//           const QString error = process.readAllStandardError();
//           if (!error.isEmpty()) {
//            qDebug () << "Exit status: " << process.exitStatus() << ", Error: " << error;
//           }
//            return 0;
//        }
//    const QString output = process.readAllStandardOutput();
//    return output;
//}

//QString Compiler::getOutput() {
//    return this->output;
//}

//void Compiler::setOutput(QString newOutput) {
//    this->output = newOutput;
//    emit outputChanged();
//}
