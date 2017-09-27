#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <vector>
#include <iostream>
#include <thread>
#include <string>
#include <QString>
#include <QQmlContext>
#include <sstream>
#include <QWindow>
#include <chrono>
#include <stdlib.h>

#include <tools.h>
#include "progress.h"

void test(Progress *p, QGuiApplication * app) {
    std::vector<gtarma::model::Item> items = gtarma::GetFiles();
    p->setProgressTotalCount(items.size());

    std::stringstream armaPath; armaPath << std::getenv("LOCALAPPDATA") << "\\Arma 3\\MPMissionsCache\\";

    for (int i = 0; i < items.size(); i++) {
        gtarma::model::Item item = items[i];
        std::string path = armaPath.str();
        gtarma::DownloadFile(item, path);
        float progress = (float)(i + 1) / (float)(items.size());
        p->setProgressvalue(progress);
        p->setProgressCompletedCount(p->progressCompletedCount() + 1);
        std::stringstream ss; ss << p->progressCompletedCount() << " out of " << p->progressTotalCount();
        p->setSubtext(QString::fromStdString(ss.str()));
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    QWindowList windows = app->allWindows();
    for (int i = 0; i < windows.size(); i++)
    {
        QWindow * window = windows[i];
        window->close();
        delete window;
    }
    app->exit();
}


int main(int argc, char *argv[])
{
    QGuiApplication * app = new QGuiApplication(argc, argv);

    //items.join();

    QQmlApplicationEngine engine;

    //float progress = 6.0;
    Progress * p = new Progress();
    p->setProgressvalue(4.0);
    p->setProgressCompletedCount(0);
    p->setProgressTotalCount(0);
    p->setSubtext(QString(""));
    QQmlContext *ctxt = engine.rootContext();
    ctxt->setContextProperty("progressData", p);

    std::thread items = std::thread(test, p, app);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    //QObject *pbar = engine.findChild<QObject*>("downloadProgressBar");

    return app->exec();
}
