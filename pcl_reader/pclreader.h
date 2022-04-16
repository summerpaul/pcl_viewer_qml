#ifndef PCLREADER_H
#define PCLREADER_H
#include <QtQuick3D/QQuick3DGeometry>
#include <QtGui/QVector3D>
#include <QObject>

#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

#include <memory>
class PCLReader : public QQuick3DGeometry
{
    Q_OBJECT
    QML_NAMED_ELEMENT(PCLReader)
    Q_PROPERTY(QString pclFilePath READ pclFilePath WRITE setPclFilePath NOTIFY pclFilePathChanged)
public:
    explicit PCLReader();
    QString pclFilePath() const;
public slots:
    void setPclFilePath(QString pcl_file_path);
signals:
    void pclFilePathChanged();

private:
    void updateGeometry(pcl::PointCloud<pcl::PointXYZ>::Ptr & pcd_points);
private:
    QString PclFilePath_;

};

#endif // PCLREADER_H
