#ifndef CALIBRATIONTOOLKIT_H
#define CALIBRATIONTOOLKIT_H

#include<qwidget.h>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<qlabel.h>
#include<qpushbutton.h>
#include<qtablewidget.h>
#include<qfiledialog.h>
#include<qimage.h>
#include<qdatetime.h>
#include<qtabwidget.h>

#include<opencv2/opencv.hpp>

#include<rosinterface.h>

#include<sensor_msgs/Image.h>

#define EXTRINSICMATSTR "ExtrinsicMat"
#define CAMERAMAT "CameraMat"
#define DISTCOEFF "DistCoeff"
#define CHESSBOARDPOSE "ChessboardPose"

class CalibrationToolkitBase : public QWidget
{
    Q_OBJECT
public:
    CalibrationToolkitBase(QWidget * parent=0);
    ~CalibrationToolkitBase();
protected:
    QHBoxLayout * layout;
    QVBoxLayout * caliblayout;
    cv::Mat extrinsicmat;
    QTableWidget * extrinsicshow;
signals:
    void calibDataGrabbedSignal();
    void sensorCalibratedSignal();
    void calibResultLoadedSignal();
    void calibResultSavedSignal();
public slots:
    void grabCalibDataSlot();
    void calibrateSensorSlot();
    void loadCalibResultSlot();
    void saveCalibResultSlot();
protected:
    virtual bool grabCalibData()=0;
    virtual bool calibrateSensor()=0;
    virtual bool loadCalibResult(cv::FileStorage & fs);
    virtual bool saveCalibResult(cv::FileStorage & fs);
protected:
    void setResultShow(cv::Mat result, QTableWidget * show);
public:
    cv::Mat getExtrinsicMat();
};

class CalibrateROSCameraChessboard : public CalibrationToolkitBase
{
    Q_OBJECT
public:
    CalibrateROSCameraChessboard(QString topic, cv::Size2f patternSize, cv::Size2i patternNum, QWidget * parent=0);
    ~CalibrateROSCameraChessboard();
protected:
    ROSSub<sensor_msgs::ImageConstPtr> * camerasub;

    cv::Mat calibimage;
    QLabel * timestampshow;
    QLabel * calibimageshow;
    cv::vector<cv::Mat> calibimages;
    QTabWidget * calibimagesshow;
    QVector<QRgb> colorTable;

    cv::Size2i patternnum;
    cv::Size2f patternsize;
    double reprojectionerror;
    QLabel * reprojectionerrorshow;

    cv::vector<cv::Point3f> grid3dpoint;
    cv::vector<cv::vector<cv::Point3f> > grid3dpoints;
    cv::vector<cv::vector<cv::Point2f> > grid2dpoints;

    cv::Mat cameramat;
    QTableWidget * cameramatshow;
    cv::Mat distcoeff;
    QTableWidget * distcoeffshow;

    cv::vector<cv::Mat> chessboardposes;
    QTabWidget * chessboardposeshow;
protected slots:
    void refreshImageSlot();
protected:
    bool grabCalibData();
    bool calibrateSensor();
    bool loadCalibResult(cv::FileStorage &fs);
    bool saveCalibResult(cv::FileStorage &fs);
public:
    cv::Mat getCameraMat();
    cv::Mat getDistCoeff();
    cv::Mat getChessboardPose(int id);
    cv::vector<cv::Mat> getChessboardPoses();
};

#endif // CALIBRATIONTOOLKIT_H
