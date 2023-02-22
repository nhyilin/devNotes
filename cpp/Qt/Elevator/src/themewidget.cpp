#include "themewidget.h"
#include "ui_themewidget.h"

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QAreaSeries>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QApplication>
#include <QtCharts/QValueAxis>
#include "DataManager.h"
#include <QPainter>
#include <QDateTime>
#include <vector>

#include <iostream>
#include <sstream>
#include <QPointF>
#include <algorithm>
#include "../param_deliver.h"
#include "Net.h"
#include "Utils.h"

#define SIMPLE
#define NHYILIN

ThemeWidget::ThemeWidget(QWidget *parent) :
        QWidget(parent),
        m_listCount(1),//随机数生成的线数
        m_valueMax(1642089600),
        m_valueCount(7),
        m_dataTable_velocity(generateRandomData(velocity)),
        m_dataTable_decibel(generateRandomData(decibel)),
        m_ui(new Ui_ThemeWidgetForm) {
    m_ui->setupUi(this);
    populateThemeBox();
    populateAnimationBox();
    populateLegendBox();

    //create charts
    QChartView *chartView;
#ifndef SIMPLE
    chartView = new QChartView(createAreaChart());
    m_ui->gridLayout->addWidget(chartView, 1, 0);
    m_charts << chartView;

    chartView = new QChartView(createPieChart());
    // Funny things happen if the pie slice labels do not fit the screen, so we ignore size policy
    chartView->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    m_ui->gridLayout->addWidget(chartView, 1, 1);
    m_charts << chartView;

    //![5]
    chartView = new QChartView(createLineChart());
    m_ui->gridLayout->addWidget(chartView, 1, 2);
    //![5]
    m_charts << chartView;

    chartView = new QChartView(createBarChart(m_valueCount));
    m_ui->gridLayout->addWidget(chartView, 2, 0);
    m_charts << chartView;
#endif
    chartView = new QChartView(createSplineChart_velocityData());
    m_ui->gridLayout->addWidget(chartView, 1, 0);
    m_charts << chartView;

    chartView = new QChartView(createSplineChart_decibelData());
    m_ui->gridLayout->addWidget(chartView, 1, 1);
    m_charts << chartView;

#ifndef SIMPLE
    m_ui->gridLayout->addWidget(chartView, 2, 1);

    chartView = new QChartView(createScatterChart());
    m_ui->gridLayout->addWidget(chartView, 2, 2);
    m_charts << chartView;
#endif

    // Set defaults
    m_ui->antialiasCheckBox->setChecked(true);
    m_ui->textEdit->setPlainText("TestData.txt");

    // Set the colors from the blue theme as default ones
    QPalette pal = qApp->palette();
    pal.setColor(QPalette::Window, QRgb(0x40434a));
    pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
    qApp->setPalette(pal);

    updateUI();
}

ThemeWidget::~ThemeWidget() {
    delete m_ui;
}

DataTable ThemeWidget::generateRandomData(targetMode mode_name) {
#ifndef NHYILIN
    DataTable dataTable;

    // generate random data
    for (int i(0); i < listCount; i++) {
        DataList dataList;
        qreal yValue(0);
        for (int j(0); j < valueCount; j++) {
            yValue = yValue + QRandomGenerator::global()->bounded(valueMax / (qreal) valueCount);
            QPointF value(
                    (j + QRandomGenerator::global()->generateDouble()) * ((qreal) m_valueMax / (qreal) valueCount),
                    yValue);
            QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
            dataList << Data(value, label);
        }
        dataTable << dataList;
    }
#endif
//    DataList dataList;
    DataTable dataTable;
    std::vector<double> time_data, test_data, target_data;
    std::string train_data_path{};
    std::string test_data_path{};

    switch (mode_name) {
        case velocity:
            train_data_path = "/data/velocity/traindata.txt";
            test_data_path = "/data/velocity/testdata.txt";
            break;
        case decibel:
            train_data_path = "/data/decibel/traindata.txt";
            test_data_path = "/data/decibel/testdata.txt";
        default:
            std::cout << "default case; ";
            break;
    }

    this->read_test_data(time_data, test_data);
    dataTable << txt_data_into_dataList(time_data, test_data, m_y_min_velocity, m_y_max_velocity,m_x_time_velocity);

    return dataTable;
}


DataList
ThemeWidget::txt_data_into_dataList(const std::vector<double> &time_data, const std::vector<double> &test_data,
                                    double &y_min, double &y_max,std::vector<QDateTime>& m_time ) {
    DataList dataList;
    std::vector<QPointF> points;

    for (int i = 0; i < time_data.size(); i++) {
        int temp = static_cast<int>(time_data[i]);
        QDateTime datetime = QDateTime::fromString(QString::number(temp), "yyyyMMdd");
        m_time.push_back(datetime);
        int x = static_cast<int>(datetime.toSecsSinceEpoch());
        QPointF point(x, test_data[i]);
        QString label = "Slice " + QString::number(1);
        dataList << Data(point, label);
        points.push_back(point);
    }
    this->set_x_axes_Range(points, m_valueMin, m_valueMax);
    y_min = *min_element(test_data.begin(), test_data.end());
    y_max = *max_element(test_data.begin(), test_data.end());

    return dataList;
}


void ThemeWidget::populateThemeBox() {
    // add items to theme combobox
    m_ui->themeComboBox->addItem("Blue Cerulean", QChart::ChartThemeBlueCerulean);
    m_ui->themeComboBox->addItem("Light", QChart::ChartThemeLight);
    m_ui->themeComboBox->addItem("Dark", QChart::ChartThemeDark);
    m_ui->themeComboBox->addItem("Brown Sand", QChart::ChartThemeBrownSand);
    m_ui->themeComboBox->addItem("Blue NCS", QChart::ChartThemeBlueNcs);
    m_ui->themeComboBox->addItem("High Contrast", QChart::ChartThemeHighContrast);
    m_ui->themeComboBox->addItem("Blue Icy", QChart::ChartThemeBlueIcy);
    m_ui->themeComboBox->addItem("Qt", QChart::ChartThemeQt);
}

void ThemeWidget::populateAnimationBox() {
    // add items to animation combobox
    m_ui->animatedComboBox->addItem("No Animations", QChart::NoAnimation);
    m_ui->animatedComboBox->addItem("GridAxis Animations", QChart::GridAxisAnimations);
    m_ui->animatedComboBox->addItem("Series Animations", QChart::SeriesAnimations);
    m_ui->animatedComboBox->addItem("All Animations", QChart::AllAnimations);
}

void ThemeWidget::populateLegendBox() {
    // add items to legend combobox
    m_ui->legendComboBox->addItem("No Legend ", 0);
    m_ui->legendComboBox->addItem("Legend Top", Qt::AlignTop);
    m_ui->legendComboBox->addItem("Legend Bottom", Qt::AlignBottom);
    m_ui->legendComboBox->addItem("Legend Left", Qt::AlignLeft);
    m_ui->legendComboBox->addItem("Legend Right", Qt::AlignRight);
}

QChart *ThemeWidget::createAreaChart() const {
    QChart *chart = new QChart();
    chart->setTitle("Area chart");

    // The lower series initialized to zero values
    QLineSeries *lowerSeries = 0;
    QString name("Series ");
    int nameIndex = 0;
    for (int i(0); i < m_dataTable_velocity.count(); i++) {
        QLineSeries *upperSeries = new QLineSeries(chart);
        for (int j(0); j < m_dataTable_velocity[i].count(); j++) {
            Data data = m_dataTable_velocity[i].at(j);
            if (lowerSeries) {
                const QVector<QPointF> &points = lowerSeries->pointsVector();
                upperSeries->append(QPointF(j, points[i].y() + data.first.y()));
            } else {
                upperSeries->append(QPointF(j, data.first.y()));
            }
        }
        QAreaSeries *area = new QAreaSeries(upperSeries, lowerSeries);
        area->setName(name + QString::number(nameIndex));
        nameIndex++;
        chart->addSeries(area);
        lowerSeries = upperSeries;
    }

    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setRange(0, m_valueCount - 1);
    chart->axes(Qt::Vertical).first()->setRange(0, m_valueMax);

    // Add space to label to add space between labels and axis
    QValueAxis *axisY = qobject_cast<QValueAxis *>(chart->axes(Qt::Vertical).first());
    Q_ASSERT(axisY);
    axisY->setLabelFormat("%.1f  ");

    return chart;
}

QChart *ThemeWidget::createBarChart(int valueCount) const {
    Q_UNUSED(valueCount);
    QChart *chart = new QChart();
    chart->setTitle("Bar chart");

    QStackedBarSeries *series = new QStackedBarSeries(chart);
    for (int i(0); i < m_dataTable_velocity.count(); i++) {
        QBarSet *set = new QBarSet("Bar set " + QString::number(i));
        for (const Data &data: m_dataTable_velocity[i])
            *set << data.first.y();
        series->append(set);
    }
    chart->addSeries(series);

    chart->createDefaultAxes();
    chart->axes(Qt::Vertical).first()->setRange(0, m_valueMax * 2);
    // Add space to label to add space between labels and axis
    QValueAxis *axisY = qobject_cast<QValueAxis *>(chart->axes(Qt::Vertical).first());
    Q_ASSERT(axisY);
    axisY->setLabelFormat("%.1f  ");

    return chart;
}

QChart *ThemeWidget::createLineChart() const {
    //![1]
    QChart *chart = new QChart();
    chart->setTitle("Line chart");

    QString name("Series ");
    int nameIndex = 0;
    for (const DataList &list: m_dataTable_velocity) {
        QLineSeries *series = new QLineSeries(chart);
        for (const Data &data: list)
            series->append(data.first);
        series->setName(name + QString::number(nameIndex));
        nameIndex++;
        chart->addSeries(series);
    }
    //![2]

    //![3]
    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setRange(0, m_valueMax);
    chart->axes(Qt::Vertical).first()->setRange(0, m_valueCount);
    //![3]
    //![4]
    // Add space to label to add space between labels and axis
    QValueAxis *axisY = qobject_cast<QValueAxis *>(chart->axes(Qt::Vertical).first());
    Q_ASSERT(axisY);
    axisY->setLabelFormat("%.1f  ");
    //![4]

    return chart;
}

QChart *ThemeWidget::createPieChart() const {
    QChart *chart = new QChart();
    chart->setTitle("Pie chart");

    QPieSeries *series = new QPieSeries(chart);
    for (const Data &data: m_dataTable_velocity[0]) {
        QPieSlice *slice = series->append(data.second, data.first.y());
        if (data == m_dataTable_velocity[0].first()) {
            // Show the first slice exploded with label
            slice->setLabelVisible();
            slice->setExploded();
            slice->setExplodeDistanceFactor(0.5);
        }
    }
    series->setPieSize(0.4);
    chart->addSeries(series);

    return chart;
}

#include <string>
#include <sstream>
#include <QMainWindow>
#include <QDateTimeAxis>

std::string formatDate(int dateInt) {
    std::ostringstream oss;
    oss << dateInt;
    std::string dateStr = oss.str();
    if (dateStr.length() != 8) {
        return "";
    }
    dateStr = dateStr.substr(0, 4) + "-" + dateStr.substr(4, 2) + "-" + dateStr.substr(6, 2);
    return dateStr;
}


QChart *ThemeWidget::createSplineChart_velocityData() const {
    /*速度*/
    QChart *chart = new QChart();
    chart->setTitle("velocity data");
    QString name("Series ");
    int nameIndex = 0;

    QDateTimeAxis *axisX = new QDateTimeAxis;
    QValueAxis *axisY = new QValueAxis();
    for (const DataList &list: m_dataTable_velocity) {
        QSplineSeries *series = new QSplineSeries(chart);
        for (const Data &data: list) {
            series->append(data.first);
        }
        series->setName(name + QString::number(nameIndex));
        nameIndex++;
        chart->addSeries(series);
        series->attachAxis(axisX);

        axisX->setFormat("yyyy/MM/dd");
        axisX->setTitleText("Date");
        axisX->setLabelsAngle(30);
        axisX->setRange(QDateTime::fromSecsSinceEpoch(m_valueMin), QDateTime::fromSecsSinceEpoch(m_valueMax));
        chart->addAxis(axisX, Qt::AlignBottom);

        axisY->setRange(m_y_min_velocity, m_y_max_velocity);
        chart->addAxis(axisY, Qt::AlignRight);
        series->attachAxis(axisY);
    }

    return chart;

}

QChart *ThemeWidget::createSplineChart_decibelData() const {
    /*分贝*/
    QChart *chart = new QChart();
    chart->setTitle("decibel data");
    QString name("Series ");
    int nameIndex = 0;

    QDateTimeAxis *axisX = new QDateTimeAxis;
    QValueAxis *axisY = new QValueAxis();
    for (const DataList &list: m_dataTable_decibel) {
        QSplineSeries *series = new QSplineSeries(chart);
        for (const Data &data: list) {
            series->append(data.first);
        }
        series->setName(name + QString::number(nameIndex));
        nameIndex++;
        chart->addSeries(series);
        series->attachAxis(axisX);

        axisX->setFormat("yyyy/MM/dd");
        axisX->setTitleText("Date");
        axisX->setLabelsAngle(30);
        axisX->setRange(QDateTime::fromSecsSinceEpoch(m_valueMin), QDateTime::fromSecsSinceEpoch(m_valueMax));
        chart->addAxis(axisX, Qt::AlignBottom);

        axisY->setRange(m_y_min_decibel, m_y_max_decibel);

        chart->addAxis(axisY, Qt::AlignRight);
        series->attachAxis(axisY);

    }

    return chart;

}

QChart *ThemeWidget::createScatterChart() const {
    // scatter chart
    QChart *chart = new QChart();
    chart->setTitle("Scatter chart");
    QString name("Series ");
    int nameIndex = 0;
    for (const DataList &list: m_dataTable_velocity) {
        QScatterSeries *series = new QScatterSeries(chart);
        for (const Data &data: list)
            series->append(data.first);
        series->setName(name + QString::number(nameIndex));
        nameIndex++;
        chart->addSeries(series);
    }

    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setRange(0, m_valueMax);
    chart->axes(Qt::Vertical).first()->setRange(0, m_valueCount);
    // Add space to label to add space between labels and axis
    QValueAxis *axisY = qobject_cast<QValueAxis *>(chart->axes(Qt::Vertical).first());
    Q_ASSERT(axisY);
    axisY->setLabelFormat("%.1f  ");
    return chart;
}

void ThemeWidget::updateUI() {
    //![6]
    QChart::ChartTheme theme = static_cast<QChart::ChartTheme>(
            m_ui->themeComboBox->itemData(m_ui->themeComboBox->currentIndex()).toInt());
    //![6]
    const auto charts = m_charts;
    if (!m_charts.isEmpty() && m_charts.at(0)->chart()->theme() != theme) {
        for (QChartView *chartView: charts) {
            //![7]
            chartView->chart()->setTheme(theme);
            //![7]
        }

        // Set palette colors based on selected theme
        //![8]
        QPalette pal = window()->palette();
        if (theme == QChart::ChartThemeLight) {
            pal.setColor(QPalette::Window, QRgb(0xf0f0f0));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
            //![8]
        } else if (theme == QChart::ChartThemeDark) {
            pal.setColor(QPalette::Window, QRgb(0x121218));
            pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
        } else if (theme == QChart::ChartThemeBlueCerulean) {
            pal.setColor(QPalette::Window, QRgb(0x40434a));
            pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
        } else if (theme == QChart::ChartThemeBrownSand) {
            pal.setColor(QPalette::Window, QRgb(0x9e8965));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        } else if (theme == QChart::ChartThemeBlueNcs) {
            pal.setColor(QPalette::Window, QRgb(0x018bba));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        } else if (theme == QChart::ChartThemeHighContrast) {
            pal.setColor(QPalette::Window, QRgb(0xffab03));
            pal.setColor(QPalette::WindowText, QRgb(0x181818));
        } else if (theme == QChart::ChartThemeBlueIcy) {
            pal.setColor(QPalette::Window, QRgb(0xcee7f0));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        } else {
            pal.setColor(QPalette::Window, QRgb(0xf0f0f0));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        }
        window()->setPalette(pal);
    }

    // Update antialiasing
    //![11]
    bool checked = m_ui->antialiasCheckBox->isChecked();
    for (QChartView *chart: charts)
        chart->setRenderHint(QPainter::Antialiasing, checked);
    //![11]

    // Update animation options
    //![9]
    QChart::AnimationOptions options(
            m_ui->animatedComboBox->itemData(m_ui->animatedComboBox->currentIndex()).toInt());
    if (!m_charts.isEmpty() && m_charts.at(0)->chart()->animationOptions() != options) {
        for (QChartView *chartView: charts)
            chartView->chart()->setAnimationOptions(options);
    }
    //![9]

    // Update legend alignment
    //![10]
    Qt::Alignment alignment(
            m_ui->legendComboBox->itemData(m_ui->legendComboBox->currentIndex()).toInt());

    if (!alignment) {
        for (QChartView *chartView: charts)
            chartView->chart()->legend()->hide();
    } else {
        for (QChartView *chartView: charts) {
            chartView->chart()->legend()->setAlignment(alignment);
            chartView->chart()->legend()->show();
        }
    }
    //![10]
}

void ThemeWidget::on_pushButton_clicked() {
    std::string filename = this->m_ui->textEdit->toPlainText().toStdString();
    DataManager::instance()->getRandomPoints(filename);
}


void ThemeWidget::read_test_data(std::vector<double> &col2, std::vector<double> &col3) const {
    // 打开txt文件
    std::ifstream infile("/Users/peiyilin/dev/devNotes/Python/GenerateDOCX/src/data.txt");

    // 逐行读取txt文件中的数据
    std::string line;
    while (getline(infile, line)) {
        // 使用stringstream将一行数据分解为三个double值
        double x, y;
        std::stringstream ss(line);
        ss >> x >> y;

        // 将读取的三个double值分别存入三个vector中
        col2.push_back(x);
        col3.push_back(y);
    }

    // 关闭文件
    infile.close();

}

void ThemeWidget::set_x_axes_Range(const std::vector<QPointF> &points, int &minX, int &maxX) {
    /*
    * 获取绘图横轴时间范围
    * */

    double xMin = std::numeric_limits<double>::max();  // x 轴的最小值
    double xMax = std::numeric_limits<double>::min();  // x 轴的最大值
    for (const auto &p: points) {
        if (p.x() < xMin)
            xMin = p.x();
        if (p.x() > xMax)
            xMax = p.x();
    }
    minX = static_cast<int>(xMin);
    maxX = static_cast<int>(xMax);
}

void ThemeWidget::using_net(std::vector<double> &input_list, std::vector<double> &target_list,
                            std::vector<double> &label_list, const std::string &train_data_path,
                            const std::string &test_data_path) {
    // Create neural network object
    Net net;

    // Read training data
    const vector<Sample> trainDataSet = Utils::getTrainData(PROJECT_PATH + train_data_path);

    // Training neural network
    net.train(trainDataSet);

    // Prediction of samples using neural network
    const vector<Sample> testDataSet = Utils::getTestData(PROJECT_PATH + test_data_path);
    vector<Sample> predSet = net.predict(testDataSet);

//    std::vector<double> input_list{};
//    std::vector<double> target_list{};
//    std::vector<double> label_list{};
    for (auto &pred: predSet) {
        pred.display();
        input_list.push_back(pred.feature[0]);
        target_list.push_back(pred.feature[1]);
        label_list.push_back(pred.label[0]);
    }

}