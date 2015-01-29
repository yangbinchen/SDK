#ifndef VIRTUALSCAN_H
#define VIRTUALSCAN_H

#include<QVector>
#include<sensor_msgs/PointCloud2.h>

class VirtualScan
{
public:
    sensor_msgs::PointCloud2ConstPtr velodynedata;
protected:
    int beamnum;
    double step;
    double minfloor;
    double maxceiling;
    QVector<QVector<double> > dp;
public:
    VirtualScan();
    virtual ~VirtualScan();
public:
    void calculateVirtualScans(int beamNum, double heightStep, double minFloor, double maxCeiling);
    void getUpperVirtualScan(double theta, double maxFloor, double minCeiling, QVector<double> & virtualScan, QVector<double> & heights);
    void getLowerVirtualScan(double theta, double maxFloor, double minCeiling, QVector<double> & virtualScan, QVector<double> & heights);
public:
    int getBeamNum();
    double getHeightStep();
    double getMinFloor();
    double getMaxCeiling();
};

#endif // VIRTUALSCAN_H
