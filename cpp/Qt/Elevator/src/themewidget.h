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
        none,
        velocity,           //速度
        decibel,             //分贝
        vibration            //震动
    };
    enum dataType {
        none_type,
        test,             //描点
        ideal,              //曲线
        label               //准确率
    };
    enum drawType {
        none_draw,
        decibel_draw,//分贝
        velocity_draw,//速度
        vibration_draw//震动
    };
    int m_data_type = dataType::none_type;

    DataTable generateRandomData(targetMode mode_name);

    DataList
    txt_data_into_dataList(const std::vector<double> &time_data, const std::vector<double> &test_data,
                           int &x_min, int &x_max, double &y_min, double &y_max,
                           std::vector<QDateTime> &m_time);


    void populateThemeBox();

    void populateAnimationBox();

    void populateLegendBox();

    void connectSignals();

    void movePercentage2PicCenter(const std::vector<double> &test_data, std::vector<double> &label_data_velocity);

    static void
    read_testdata_data(std::vector<double> &col2, std::vector<double> &col3, const std::string &test_data_path,
                       const dataType &data_type);

    void set_x_axes_Range(const std::vector<QPointF> &points, int &minX, int &maxX);

    static void using_net(std::vector<double> &input_list, std::vector<double> &target_list,
                          std::vector<double> &label_list, const std::string &train_data_path,
                          const std::string &test_data_path);

    QChart *createAreaChart() const;

    QChart *createBarChart(int valueCount) const;

    QChart *createPieChart() const;

    QChart *createLineChart() const;

    QChart *createSplineChart(const drawType &draw_type) const;//画图

    QChart *createSplineChart_velocityData() const;         //速度
    QChart *createSplineChart_decibelData() const;          //声音分贝值

    QChart *createScatterChart() const;


private:
    int m_listCount;
    int m_valueMin_velocity = 0;                                //速度x轴最小值
    int m_valueMax_velocity = 0;                                //速度x轴最大值

    int m_valueMin_decibel = 0;                                 //分贝x轴最小值
    int m_valueMax_decibel = 0;                                 //分贝x轴最大值

    int m_valueMin_vibration = 0;                                 //分贝x轴最小值
    int m_valueMax_vibration = 0;                                 //分贝x轴最大值

    int m_valueCount;

    double m_y_min_velocity = 0;                                //速度y轴最小值
    double m_y_max_velocity = 0;                                //速度y轴最大值

    double m_y_min_decibel = 0;                                 //分贝y轴最小值
    double m_y_max_decibel = 0;                                 //分贝y轴最大值

    double m_y_min_vibration = 0;                                 //震动y轴最小值
    double m_y_max_vibration = 0;                                 //震动y轴最大值

    std::vector<QDateTime> m_x_time_velocity;
    std::vector<QDateTime> m_x_time_decibel;
    std::vector<QDateTime> m_x_time_vibration;

    QList<QChartView *> m_charts;

    DataTable m_dataTable_velocity;
    DataTable m_dataTable_decibel;
    DataTable m_dataTable_vibration;

    std::vector<double> time_data_velocity, target_data_velocity, test_data_velocity, label_data_velocity;  //从txt中读取的数据
    std::vector<double> time_data_decibel, target_data_decibel, test_data_decibel, label_data_decibel;
    std::vector<double> time_data_vibration, target_data_vibration, test_data_vibration, label_data_vibration;

    /*以下为训练完成的数据*/
    std::vector<double> input_list_velocity;                //测试数据
    std::vector<double> target_list_velocity;               //理想数据
    std::vector<double> label_list_velocity;                //标签数据，判分系统

    std::vector<double> input_list_decibel;
    std::vector<double> target_list_decibel;
    std::vector<double> label_list_decibel;

    std::vector<double> input_list_vibration;
    std::vector<double> target_list_vibration;
    std::vector<double> label_list_vibration;

    Ui_ThemeWidgetForm *m_ui;
};

#endif /* THEMEWIDGET_H */
