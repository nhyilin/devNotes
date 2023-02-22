#ifndef THEMEWIDGET_H
#define THEMEWIDGET_H

#include <QtWidgets/QWidget>
#include <QtCharts/QChartGlobal>

QT_BEGIN_NAMESPACE
class QComboBox;

class QCheckBox;

class Ui_ThemeWidgetForm;

QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
    class QChartView;

    class QChart;
QT_CHARTS_END_NAMESPACE

typedef QPair<QPointF, QString> Data;
typedef QList<Data> DataList;
typedef QList<DataList> DataTable;

QT_CHARTS_USE_NAMESPACE

class ThemeWidget : public QWidget {
Q_OBJECT
public:
    explicit ThemeWidget(QWidget *parent = 0);

    ~ThemeWidget();

private Q_SLOTS:

    void updateUI();

    void on_pushButton_clicked();

private:
    enum targetMode {
        velocity,           //速度
        decibel             //分贝
    };

    DataTable generateRandomData(targetMode mode_name);

    DataList
    txt_data_into_dataList(const std::vector<double> &time_data, const std::vector<double> &test_data, double &m_x_min,
                           double &m_y_max, std::vector<QDateTime> &m_time);


    void populateThemeBox();

    void populateAnimationBox();

    void populateLegendBox();

    void connectSignals();

    void read_test_data(std::vector<double> &col2, std::vector<double> &col3) const;

    void set_x_axes_Range(const std::vector<QPointF> &points, int &minX, int &maxX);

    void using_net(std::vector<double> &input_list, std::vector<double> &target_list,
                   std::vector<double> &label_list, const std::string &train_data_path,
                   const std::string &test_data_path);

    QChart *createAreaChart() const;

    QChart *createBarChart(int valueCount) const;

    QChart *createPieChart() const;

    QChart *createLineChart() const;

    QChart *createSplineChart_velocityData() const;//速度
    QChart *createSplineChart_decibelData() const;//声音分贝值

    QChart *createScatterChart() const;


private:
    int m_listCount;
    int m_valueMax;
    int m_valueMin;
    int m_valueCount;
    double m_y_min_velocity;//速度y轴最小值
    double m_y_max_velocity;//速度y轴最大值

    double m_y_min_decibel;//分贝y轴最小值
    double m_y_max_decibel;//分贝y轴最大值

    std::vector<QDateTime> m_x_time_velocity;
    std::vector<QDateTime> m_x_time_decibel;
    QList<QChartView *> m_charts;
    DataTable m_dataTable_velocity;
    DataTable m_dataTable_decibel;


    Ui_ThemeWidgetForm *m_ui;
};

#endif /* THEMEWIDGET_H */
