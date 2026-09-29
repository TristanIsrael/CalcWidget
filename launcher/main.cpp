#include <QDebug>
#include <QProcess>
#include <QCoreApplication>

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    QProcess process;

    QString dirPath(QCoreApplication::applicationDirPath());
    QStringList dirs = dirPath.split("/");

    //Launcher is in the subfolder Library/LoginItems
    //of the application at the path /Applications/EasyCalc.app
    //Its complete path is /Applications/EasyCalc.app/Library/LoginItems/EasyCalcLauncher.app/Contents/MacOS/EasyCalcLauncher
    //We want to launch the app /Applications/EasyCalc.app
    //it means all dirs minus the 5 last

    QString appPath;
    for(int i = 0 ; i < dirs.length() - 5 ; i++) {
        appPath.append("/").append(dirs[i]);
    }
    appPath.append("/Contents/MacOS/EasyCalc");

    qDebug() << "Program to start:" << appPath;

    process.setProgram(appPath);
    process.startDetached();
}
