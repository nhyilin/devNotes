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
#include <string>
#include <QDateTimeAxis>
#include "../param_deliver.h"
#include "Net.h"
#include "Utils.h"

#define _REFACTOR

ThemeWidget::ThemeWidget(QWidget *parent)
        : QWidget(parent),
          m_listCount(1),  // 随机数生成的线数
        //        m_valueMax(1642089600),
          m_valueCount(7),
          m_dataTable_velocity(generateRandomData(velocity)),
          m_dataTable_decibel(generateRandomData(decibel)),
          m_dataTable_vibration(generateRandomData(vibration)),
          m_ui(new Ui_ThemeWidgetForm) {
    m_ui->setupUi(this);
    populateThemeBox();
    populateAnimationBox();
    populateLegendBox();

    // create charts
    QChartView *chartView;
    chartView = new QChartView(createSplineChart(drawType::velocity_draw));
    m_ui->gridLayout->addWidget(chartView, 1, 0);
    m_charts << chartView;

    chartView = new QChartView(createSplineChart(drawType::decibel_draw));
    m_ui->gridLayout->addWidget(chartView, 1, 1);
    m_charts << chartView;

    chartView = new QChartView(createSplineChart(drawType::vibration_draw));
    m_ui->gridLayout->addWidget(chartView, 1, 2);
    m_charts << chartView;

    // Set defaults
    m_ui->antialiasCheckBox->setChecked(true);

    // Set the colors from the blue theme as default ones
    QPalette pal = qApp->palette();
    pal.setColor(QPalette::Window, QRgb(0x40434a));
    pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
    qApp->setPalette(pal);

    updateUI();
}

ThemeWidget::~ThemeWidget() { delete m_ui; }

DataTable ThemeWidget::generateRandomData(targetMode mode_name) {
    DataTable dataTable;

#ifdef Q_OS_MAC
    std::string velocity_test_data_path = PROJECT_PATH + string("/data/velocity/testdata.txt");
    std::string velocity_train_data_path = PROJECT_PATH +string("/data/velocity/traindata.txt");

    std::string decibel_test_data_path = PROJECT_PATH + string("/data/decibel/testdata.txt");
    std::string decibel_train_data_path = PROJECT_PATH +string("/data/decibel/traindata.txt");

    std::string vibration_test_data_path = PROJECT_PATH + string("/data/vibration/testdata.txt");
    std::string vibration_train_data_path = PROJECT_PATH +string("/data/vibration/traindata.txt");
#endif

#ifdef Q_OS_WIN
    std::string velocity_test_data_path = string("./data/velocity/testdata.txt");
    std::string velocity_train_data_path = string("./data/velocity/traindata.txt");

    std::string decibel_test_data_path = string("./data/decibel/testdata.txt");
    std::string decibel_train_data_path = string("./data/decibel/traindata.txt");

    std::string vibration_test_data_path = string("./data/vibration/testdata.txt");
    std::string vibration_train_data_path = string("./data/vibration/traindata.txt");
#endif

    switch (mode_name) {
        case velocity:
            read_testdata_data(time_data_velocity, target_data_velocity, velocity_test_data_path, dataType::ideal);
            dataTable << txt_data_into_dataList(
                    time_data_velocity, target_data_velocity, m_valueMin_velocity,
                    m_valueMax_velocity, m_y_min_velocity, m_y_max_velocity,
                    m_x_time_velocity);
            read_testdata_data(time_data_velocity, test_data_velocity, velocity_test_data_path, dataType::test);
            dataTable << txt_data_into_dataList(
                    time_data_velocity, test_data_velocity, m_valueMin_velocity,
                    m_valueMax_velocity, m_y_min_velocity, m_y_max_velocity,
                    m_x_time_velocity);
            using_net(test_data_velocity, target_data_velocity, label_data_velocity, velocity_train_data_path,
                      velocity_test_data_path);
            movePercentage2PicCenter(test_data_velocity, label_data_velocity);
            dataTable << txt_data_into_dataList(
                    time_data_velocity, label_data_velocity, m_valueMin_velocity,
                    m_valueMax_velocity, m_y_min_velocity, m_y_max_velocity,
                    m_x_time_velocity);

            break;
        case decibel:
            read_testdata_data(time_data_decibel, target_data_decibel, decibel_test_data_path, dataType::ideal);
            dataTable << txt_data_into_dataList(
                    time_data_decibel, target_data_decibel, m_valueMin_decibel,
                    m_valueMax_decibel, m_y_min_decibel, m_y_max_decibel,
                    m_x_time_decibel);
            read_testdata_data(time_data_decibel, test_data_decibel, decibel_test_data_path, dataType::test);
            dataTable << txt_data_into_dataList(time_data_decibel, test_data_decibel,
                                                m_valueMin_decibel,
                                                m_valueMax_decibel, m_y_min_decibel,
                                                m_y_max_decibel, m_x_time_decibel);

            using_net(test_data_decibel, target_data_decibel, label_data_decibel,
                      decibel_train_data_path, decibel_test_data_path);
            movePercentage2PicCenter(test_data_decibel, label_data_decibel);
            dataTable << txt_data_into_dataList(time_data_decibel, label_data_decibel,
                                                m_valueMin_decibel,
                                                m_valueMax_decibel, m_y_min_decibel,
                                                m_y_max_decibel, m_x_time_decibel);
        case vibration:
            read_testdata_data(time_data_vibration, target_data_vibration, vibration_test_data_path, dataType::ideal);
            dataTable << txt_data_into_dataList(
                    time_data_vibration, target_data_vibration, m_valueMin_vibration,
                    m_valueMax_vibration, m_y_min_vibration, m_y_max_vibration,
                    m_x_time_vibration);
            read_testdata_data(time_data_vibration, test_data_vibration, vibration_test_data_path, dataType::test);
            dataTable << txt_data_into_dataList(
                    time_data_vibration, test_data_vibration, m_valueMin_vibration,
                    m_valueMax_vibration, m_y_min_vibration, m_y_max_vibration,
                    m_x_time_vibration);
            using_net(test_data_vibration, target_data_vibration,
                      label_data_vibration, vibration_train_data_path,
                      vibration_test_data_path);
            movePercentage2PicCenter(test_data_vibration, label_data_vibration);
            dataTable << txt_data_into_dataList(
                    time_data_vibration, label_data_vibration, m_valueMin_vibration,
                    m_valueMax_vibration, m_y_min_vibration, m_y_max_vibration,
                    m_x_time_vibration);

        default:
            std::cout << "default case; ";
            break;
    }

    return dataTable;
}

DataList ThemeWidget::txt_data_into_dataList(
        const std::vector<double> &time_data, const std::vector<double> &test_data,
        int &x_min, int &x_max, double &y_min, double &y_max,
        std::vector<QDateTime> &m_time) {
    DataList dataList;
    std::vector<QPointF> points;

    for (int i = 0; i < time_data.size(); i++) {
        int temp = static_cast<int>(time_data[i]);
        QDateTime datetime =
                QDateTime::fromString(QString::number(temp), "yyyyMMdd");
        m_time.push_back(datetime);
        int x = static_cast<int>(datetime.toSecsSinceEpoch());
        QPointF point(x, test_data[i]);
        QString label = "Slice " + QString::number(1);
        dataList << Data(point, label);
        points.push_back(point);
    }
    if (x_max == 0) {
        this->set_x_axes_Range(points, x_min, x_max);
        y_min = *min_element(test_data.begin(), test_data.end());
        y_max = *max_element(test_data.begin(), test_data.end());
    }

    return dataList;
}

void ThemeWidget::populateThemeBox() {
    // add items to theme combobox
    m_ui->themeComboBox->addItem("Brown Sand", QChart::ChartThemeBrownSand);
    m_ui->themeComboBox->addItem("Blue Cerulean", QChart::ChartThemeBlueCerulean);
    m_ui->themeComboBox->addItem("Light", QChart::ChartThemeLight);
    m_ui->themeComboBox->addItem("Dark", QChart::ChartThemeDark);
    m_ui->themeComboBox->addItem("Blue NCS", QChart::ChartThemeBlueNcs);
    m_ui->themeComboBox->addItem("High Contrast", QChart::ChartThemeHighContrast);
    m_ui->themeComboBox->addItem("Blue Icy", QChart::ChartThemeBlueIcy);
    m_ui->themeComboBox->addItem("Qt", QChart::ChartThemeQt);
}

void ThemeWidget::populateAnimationBox() {
    // add items to animation combobox
    m_ui->animatedComboBox->addItem("No Animations", QChart::NoAnimation);
    m_ui->animatedComboBox->addItem("GridAxis Animations",
                                    QChart::GridAxisAnimations);
    m_ui->animatedComboBox->addItem("Series Animations",
                                    QChart::SeriesAnimations);
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
    //    chart->axes(Qt::Vertical).first()->setRange(0, m_valueMax);

    // Add space to label to add space between labels and axis
    QValueAxis *axisY =
            qobject_cast<QValueAxis *>(chart->axes(Qt::Vertical).first());
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
        for (const Data &data: m_dataTable_velocity[i]) *set << data.first.y();
        series->append(set);
    }
    chart->addSeries(series);

    chart->createDefaultAxes();
    //    chart->axes(Qt::Vertical).first()->setRange(0, m_valueMax * 2);
    // Add space to label to add space between labels and axis
    QValueAxis *axisY =
            qobject_cast<QValueAxis *>(chart->axes(Qt::Vertical).first());
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
        for (const Data &data: list) series->append(data.first);
        series->setName(name + QString::number(nameIndex));
        nameIndex++;
        chart->addSeries(series);
    }
    //![2]

    //![3]
    chart->createDefaultAxes();
    //    chart->axes(Qt::Horizontal).first()->setRange(0, m_valueMax);
    chart->axes(Qt::Vertical).first()->setRange(0, m_valueCount);
    //![3]
    //![4]
    // Add space to label to add space between labels and axis
    QValueAxis *axisY =
            qobject_cast<QValueAxis *>(chart->axes(Qt::Vertical).first());
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

std::string formatDate(int dateInt) {
    std::ostringstream oss;
    oss << dateInt;
    std::string dateStr = oss.str();
    if (dateStr.length() != 8) {
        return "";
    }
    dateStr = dateStr.substr(0, 4) + "-" + dateStr.substr(4, 2) + "-" +
              dateStr.substr(6, 2);
    return dateStr;
}

QChart *ThemeWidget::createSplineChart(const drawType &draw_type) const {
    /*
     * 画图
     * decibel_draw, 分贝
     * velocity_draw, 速度
     * vibration_draw, 震动
     * */
    QChart *chart;
    chart = new QChart();
    if (draw_type == drawType::velocity_draw)
        chart->setTitle("velocity data");
    else if (draw_type == drawType::decibel_draw)
        chart->setTitle("decibel data");
    else if (draw_type == drawType::vibration_draw)
        chart->setTitle("vibration data");
    else
        std::cerr << "please check draw type!\n";

    QDateTimeAxis *axisX;
    axisX = new QDateTimeAxis;
    QValueAxis *axisY;
    axisY = new QValueAxis();

    if (draw_type == drawType::velocity_draw) {
        for (int i = 0; i < m_dataTable_velocity.size(); ++i) {
            // 暂时以i为标志来分辨画曲线或是描点图，虽然简单粗暴，但大规模重构代码之前，最行之有效
            if (i == 0) {
                QSplineSeries *series;
                series = new QSplineSeries(chart);
                for (const Data &data: m_dataTable_velocity[i]) {
                    series->append(data.first);
                }
                chart->addSeries(series);
                series->attachAxis(axisX);
                series->attachAxis(axisY);

            } else if (i == 1 || i == 2) {
                QScatterSeries *series;
                series = new QScatterSeries(chart);
                for (const Data &data: m_dataTable_velocity[i]) {
                    series->append(data.first);
                }
                chart->addSeries(series);
                series->attachAxis(axisX);
                series->attachAxis(axisY);
            } else
                std::cerr << "please check\n";
        }
    } else if (draw_type == drawType::decibel_draw) {
        for (int i = 0; i < m_dataTable_decibel.size(); i++) {
            if (i == 0) {
                QSplineSeries *series;
                series = new QSplineSeries(chart);
                for (const Data &data: m_dataTable_decibel[i]) {
                    series->append(data.first);
                }
                chart->addSeries(series);
                series->attachAxis(axisX);
                series->attachAxis(axisY);
            } else if (i == 1 || i == 2) {
                QScatterSeries *series;
                series = new QScatterSeries(chart);
                for (const Data &data: m_dataTable_decibel[i]) {
                    series->append(data.first);
                }
                chart->addSeries(series);
                series->attachAxis(axisX);
                series->attachAxis(axisY);
            } else
                std::cerr << "please check\n";
        }
    } else if (draw_type == drawType::vibration_draw) {
        for (int i = 0; i < m_dataTable_vibration.size(); ++i) {
            // 暂时以i为标志来分辨画曲线或是描点图，虽然简单粗暴，但大规模重构代码之前，最行之有效
            if (i == 0) {
                QSplineSeries *series;
                series = new QSplineSeries(chart);
                for (const Data &data: m_dataTable_vibration[i]) {
                    series->append(data.first);
                }
                chart->addSeries(series);
                series->attachAxis(axisX);
                series->attachAxis(axisY);

            } else if (i == 1 || i == 2) {
                QScatterSeries *series;
                series = new QScatterSeries(chart);
                for (const Data &data: m_dataTable_vibration[i]) {
                    series->append(data.first);
                }
                chart->addSeries(series);
                series->attachAxis(axisX);
                series->attachAxis(axisY);
            } else
                std::cerr << "please check\n";
        }
    } else
        std::cerr << "please check draw type!\n";

    axisX->setFormat("yyyy/MM/dd");
    axisX->setTitleText("Date");
    axisX->setLabelsAngle(30);

    if (draw_type == drawType::velocity_draw) {
        axisX->setRange(QDateTime::fromSecsSinceEpoch(m_valueMin_velocity),
                        QDateTime::fromSecsSinceEpoch(m_valueMax_velocity));
        axisY->setRange(m_y_min_velocity, m_y_max_velocity);
    } else if (draw_type == drawType::decibel_draw) {
        axisX->setRange(QDateTime::fromSecsSinceEpoch(m_valueMin_decibel),
                        QDateTime::fromSecsSinceEpoch(m_valueMax_decibel));
        axisY->setRange(m_y_min_decibel, m_y_max_decibel);
    } else if (draw_type == drawType::vibration_draw) {
        axisX->setRange(QDateTime::fromSecsSinceEpoch(m_valueMin_vibration),
                        QDateTime::fromSecsSinceEpoch(m_valueMax_vibration));
        axisY->setRange(m_y_min_vibration, m_y_max_vibration);
    } else
        std::cerr << "please check draw type!\n";

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignRight);

    return chart;
}

QChart *ThemeWidget::createSplineChart_velocityData() const {
    /*速度*/
    QChart *chart;
    chart = new QChart();
    chart->setTitle("velocity data");
    QString name("Series ");
    int nameIndex = 0;

    QDateTimeAxis *axisX;
    axisX = new QDateTimeAxis;
    QValueAxis *axisY;
    axisY = new QValueAxis();
    for (int i = 0; i < m_dataTable_velocity.size(); ++i) {
        // 暂时以i为标志来分辨画曲线或是描点图，虽然简单粗暴，但大规模重构代码之前，最行之有效
        if (i == 0) {
            QSplineSeries *series;
            series = new QSplineSeries(chart);
            for (const Data &data: m_dataTable_velocity[i]) {
                series->append(data.first);
            }
            chart->addSeries(series);
            series->attachAxis(axisX);
            series->attachAxis(axisY);

        } else if (i == 1 || i == 2) {
            QScatterSeries *series;
            series = new QScatterSeries(chart);
            for (const Data &data: m_dataTable_velocity[i]) {
                series->append(data.first);
            }
            chart->addSeries(series);
            series->attachAxis(axisX);
            series->attachAxis(axisY);
        } else
            std::cerr << "please check\n";
    }
    axisX->setFormat("yyyy/MM/dd");
    axisX->setTitleText("Date");
    axisX->setLabelsAngle(30);

    axisX->setRange(QDateTime::fromSecsSinceEpoch(m_valueMin_velocity),
                    QDateTime::fromSecsSinceEpoch(m_valueMax_velocity));
    axisY->setRange(m_y_min_velocity, m_y_max_velocity);

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignRight);

    return chart;
}

QChart *ThemeWidget::createSplineChart_decibelData() const {
    /*分贝*/
    QChart *chart;
    chart = new QChart();
    chart->setTitle("decibel data");

    QDateTimeAxis *axisX;
    axisX = new QDateTimeAxis;
    QValueAxis *axisY;
    axisY = new QValueAxis();
    for (int i = 0; i < m_dataTable_decibel.size(); i++) {
        if (i == 0) {
            QSplineSeries *series;
            series = new QSplineSeries(chart);
            for (const Data &data: m_dataTable_decibel[i]) {
                series->append(data.first);
            }
            chart->addSeries(series);
            series->attachAxis(axisX);
            series->attachAxis(axisY);
        } else if (i == 1 || i == 2) {
            QScatterSeries *series;
            series = new QScatterSeries(chart);
            for (const Data &data: m_dataTable_decibel[i]) {
                series->append(data.first);
            }
            chart->addSeries(series);
            series->attachAxis(axisX);
            series->attachAxis(axisY);
        } else
            std::cerr << "please check\n";
    }
    axisX->setFormat("yyyy/MM/dd");
    axisX->setTitleText("Date");
    axisX->setLabelsAngle(30);

    axisX->setRange(QDateTime::fromSecsSinceEpoch(m_valueMin_decibel),
                    QDateTime::fromSecsSinceEpoch(m_valueMax_decibel));
    axisY->setRange(m_y_min_decibel, m_y_max_decibel);

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignRight);

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
        for (const Data &data: list) series->append(data.first);
        series->setName(name + QString::number(nameIndex));
        nameIndex++;
        chart->addSeries(series);
    }

    chart->createDefaultAxes();
    //    chart->axes(Qt::Horizontal).first()->setRange(0, m_valueMax);
    chart->axes(Qt::Vertical).first()->setRange(0, m_valueCount);
    // Add space to label to add space between labels and axis
    QValueAxis *axisY =
            qobject_cast<QValueAxis *>(chart->axes(Qt::Vertical).first());
    Q_ASSERT(axisY);
    axisY->setLabelFormat("%.1f  ");
    return chart;
}

void ThemeWidget::updateUI() {
    QChart::ChartTheme theme = static_cast<QChart::ChartTheme>(
            m_ui->themeComboBox->itemData(m_ui->themeComboBox->currentIndex())
                    .toInt());
    const auto charts = m_charts;
    if (!m_charts.isEmpty() && m_charts.at(0)->chart()->theme() != theme) {
        for (QChartView *chartView: charts) {
            chartView->chart()->setTheme(theme);
            chartView->setRubberBand(QChartView::RectangleRubberBand);
//            chartView->setRubberBandZoomMode(QChartView::RubberBandZoom);
// 监听 QChartView 的 resize 事件，并在缩放时自动调整坐标轴范围
//            connect(chartView, &QChartView::rubberBandChanged, [=](const QRectF& rect, QPointF, QPointF) {
//                // 获取当前的 QChart 对象
//                QChart* chart = chartView->chart();
//
//                // 自动调整坐标轴范围以适应缩放后的图像
//                chart->zoomReset();
//                chart->zoomIn(chartView->chart()->mapToValue(rect.topLeft()));
//                chart->zoomIn(chartView->chart()->mapToValue(rect.bottomRight()));
//            });
        }

        // Set palette colors based on selected theme
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
            m_ui->animatedComboBox->itemData(m_ui->animatedComboBox->currentIndex())
                    .toInt());
    if (!m_charts.isEmpty() &&
        m_charts.at(0)->chart()->animationOptions() != options) {
        for (QChartView *chartView: charts)
            chartView->chart()->setAnimationOptions(options);
    }
    //![9]

    // Update legend alignment
    //![10]
    Qt::Alignment alignment(
            m_ui->legendComboBox->itemData(m_ui->legendComboBox->currentIndex())
                    .toInt());

    if (!alignment) {
        for (QChartView *chartView: charts) chartView->chart()->legend()->hide();
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

void ThemeWidget::read_testdata_data(std::vector<double> &col2,
                                     std::vector<double> &col3,
                                     const std::string &test_data_path,
                                     const dataType &data_type) {
    if (!col2.empty() || !col3.empty()) {
        col2.clear();
        col3.clear();
    }

    // 读取理想数据，也就是testdata.txt的第三列
    std::ifstream infile(test_data_path);
    std::string line;
    if (data_type == dataType::ideal) {
        while (getline(infile, line)) {
            // 使用stringstream将一行数据分解为三个double值
            double x, y, z;
            std::stringstream ss(line);
            ss >> x >> y >> z;

            // 将读取的三个double值分别存入三个vector中
            col2.push_back(x);

            col3.push_back(z);
        }
        infile.close();
    } else if (data_type == dataType::test) {
        while (getline(infile, line)) {
            // 使用stringstream将一行数据分解为三个double值
            double x, y, z;
            std::stringstream ss(line);
            ss >> x >> y >> z;

            // 将读取的三个double值分别存入三个vector中
            col2.push_back(x);
            col3.push_back(y);
        }
        infile.close();
    } else if (data_type == dataType::label) {
        while (getline(infile, line)) {
            // 使用stringstream将一行数据分解为三个double值
            double x, y, z, l;
            std::stringstream ss(line);
            ss >> x >> y >> z >> l;
            std::cout << l << std::endl;

            // 将读取的三个double值分别存入三个vector中
            col2.push_back(x);
            col3.push_back(l);
        }
        infile.close();
    } else
        std::cerr << "please check dataType\n";
}

void ThemeWidget::set_x_axes_Range(const std::vector<QPointF> &points,
                                   int &minX, int &maxX) {
    /*
     * 获取绘图横轴时间范围
     * */

    double xMin = std::numeric_limits<double>::max();  // x 轴的最小值
    double xMax = std::numeric_limits<double>::min();  // x 轴的最大值
    for (const auto &p: points) {
        if (p.x() < xMin) xMin = p.x();
        if (p.x() > xMax) xMax = p.x();
    }
    minX = static_cast<int>(xMin);
    maxX = static_cast<int>(xMax);
}

void ThemeWidget::using_net(std::vector<double> &input_list,
                            std::vector<double> &target_list,
                            std::vector<double> &label_list,
                            const std::string &train_data_path,
                            const std::string &test_data_path) {
    // Create neural network object
    Net net;
    // Read training data
    const vector<Sample> trainDataSet =
            Utils::getTrainData( train_data_path);
    // Training neural network
    net.train(trainDataSet);
    // Prediction of samples using neural network
    const vector<Sample> testDataSet =
            Utils::getTestData( test_data_path);
    vector<Sample> predSet = net.predict(testDataSet);

    for (auto &pred: predSet) {
        pred.display();
        input_list.push_back(pred.feature[0]);
        target_list.push_back(pred.feature[1]);
        label_list.push_back(pred.label[0]);
    }
}

void ThemeWidget::movePercentage2PicCenter(const std::vector<double> &test_data,
                                           std::vector<double> &label_data) {
    double delta = *std::max_element(test_data.begin(), test_data.end()) -
                   *std::min_element(test_data.begin(), test_data.end());
    double min = *std::min_element(test_data.begin(), test_data.end());
    for (double &i: label_data) {
        auto temp = (i * delta) + min;
        i = temp;
    }
}
