#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QCoreApplication::setApplicationName("Country Searcher");
}

MainWindow::~MainWindow()
{
    delete ui;
}



// called when manager is finished making request
void MainWindow::managerFinished(QNetworkReply *reply)
{
    // error checking
    if (reply->error()) {
        qDebug() << reply->errorString();
        return;
    }

    // turn response into a string
    QString answer = (QString)reply->readAll();

    // convert response to json
    QJsonDocument jsonResponse = QJsonDocument::fromJson(answer.toUtf8());

    // retreive array from json response
    QJsonArray jsonArray = jsonResponse.array();

    // retreive first object in the array, which holds all relevent data
    QJsonObject data = jsonArray.first().toObject();



    // ------------------------ currency info ----------------------------
    QJsonObject currencyData = data.value("currencies").toArray().first().toObject();

    QString currency = currencyData.value("name").toString();
    currency += " ( " + currencyData.value("symbol").toString() + " )";

    ui->currency->setText(currency);





    // ------------------------ capital info ----------------------------
    QString capital = data.value("capital").toString();

    ui->capital->setText(capital);
    qDebug() << data.value("capital").toString();



    // ------------------------ capital info ----------------------------
    QString region = data.value("region").toString();

    ui->region->setText(region);


    // ------------------------ population info ----------------------------
    int population = data.value("population").toInt();

    ui->population->setText(QString::number(population));

    // ------------------------ language info ----------------------------
    QJsonObject languageData = data.value("languages").toArray().first().toObject();

    ui->language->setText(languageData.value("name").toString());

    // ------------------------ timezone info ----------------------------
    QJsonValue timezone = data.value("timezones").toArray().first();

    ui->timezone->setText(timezone.toString());

    // ------------------------ area info ----------------------------
    int areaValue = data.value("area").toInt();
    QString area = QString::number(areaValue) + " km²";

    ui->area->setText(area);

}

void MainWindow::on_input_returnPressed()
{
    // connect the manager's finish signal to the managerFinsished slot
    QNetworkAccessManager *man = new QNetworkAccessManager(this);
    connect(man, &QNetworkAccessManager::finished, this, &MainWindow::managerFinished);

    // add inputted country to request
    QString country = ui->input->text();
    const QUrl url = QUrl(URLbegin + country + URLend);

    // make request
    QNetworkRequest request(url);
    man->get(request);
}
