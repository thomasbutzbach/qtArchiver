#include <QCoreApplication>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QStringList arg = QCoreApplication::arguments();
    if (arg.length() == 3) {

        QString param1(arg.at(1)); //mode
        QString param2(arg.at(2)); //filename

        if (param1 == "-u") {

            //Decompression
            QFile fi(param2);
            QFile fo(param2.replace(".fs",".db"));

            qInfo().noquote().nospace() << "Decompressing " << fi.fileName() << " to " << fo.fileName();
            if (fi.open(QFile::ReadOnly) && fo.open(QFile::WriteOnly)) {
                fo.write(qUncompress(fi.readAll()));
                fi.close();
                fo.close();
                qInfo().noquote().nospace() << "Done.";
            } else {
                qInfo().noquote().nospace() << "Error.";
            }

        } else if (param1 == "-c") {

            //Compression
            QFile fi(param2);
            QFile fo(param2.replace(".db",".fs"));

            qInfo().noquote().nospace() << "Compressing " << fi.fileName() << " to " << fo.fileName();
            if (fi.open(QFile::ReadOnly) && fo.open(QFile::WriteOnly)) {
                fo.write(qCompress(fi.readAll(), -1));
                fi.close();
                fo.close();
                qInfo().noquote().nospace() << "Done.";
            } else {
                qInfo().noquote().nospace() << "Error.";
            }

        } else {

            qInfo().noquote().nospace() << "Mode must be of type -u (decompression) or -c (compression).";

        }

    } else {

        qInfo().noquote().nospace() << "Usage: qtArchiver.exe <mode> <filename>";

    }

    return 0;
}
