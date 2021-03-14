#include "flysoft_global.h"
#include "flysoftgroundstation.h"
#include "flysoftmqttadapter.h"

void myMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString & msg)
{
    QString txt;
    QByteArray localMsg = msg.toLocal8Bit();
    const char *file = context.file ? context.file : "";
    const char *function = context.function ? context.function : "";
    //txt << QDateTime::currentDateTime().toString() <<
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "debug: %s (%s:%u, %s)\n",localMsg.constData(), file, context.line, function);
        break;
    case QtInfoMsg:
        fprintf(stderr, "info: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtWarningMsg:
        fprintf(stderr, "warning %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "critical %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtFatalMsg:
        fprintf(stderr, "fatal: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    }

    QFile outFile("log");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << txt << endl;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qInstallMessageHandler(myMessageHandler);
    FlysoftMqttAdapter *m = new FlysoftMqttAdapter();
    FlysoftGroundStation *w = new FlysoftGroundStation(m);

    w->show();
    return a.exec();
}
