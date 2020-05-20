#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager> // makes requests
#include <QNetworkReply> // handles replies
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QString URLbegin = "https://restcountries.eu/rest/v2/name/";
    QString URLend = "?fullText=true";
    Ui::MainWindow *ui;

private slots:
    void managerFinished(QNetworkReply *reply);
    void on_input_returnPressed();
};
#endif // MAINWINDOW_H
