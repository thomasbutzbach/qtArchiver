#include <QCoreApplication>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QStringList arg = QCoreApplication::arguments();
    if (arg.length() > 1) {

        QString param1(arg.at(1));

        if (param1.endsWith(".fs", Qt::CaseInsensitive)) {

            //Decompression
            QFile fi(param1);
            QFile fo(param1.replace(".fs",".db"));

            qInfo().noquote().nospace() << "Decompressing " << fi.fileName() << " to " << fo.fileName();
            if (fi.open(QFile::ReadOnly) && fo.open(QFile::WriteOnly)) {
                fo.write(qUncompress(fi.readAll()));
                fi.close();
                fo.close();
                qInfo().noquote().nospace() << "Done.";
            } else {
                qInfo().noquote().nospace() << "Error.";
            }

        } else if (param1.endsWith(".db", Qt::CaseInsensitive)) {

            //Compression
            QFile fi(param1);
            QFile fo(param1.replace(".db",".fs"));

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

            qInfo().noquote().nospace() << "File must be of type .fs (decompression) or .db (compression).";

        }

    } else {

        qInfo().noquote().nospace() << "Please provide filename as parameter.";

    }

    return 0;
}
