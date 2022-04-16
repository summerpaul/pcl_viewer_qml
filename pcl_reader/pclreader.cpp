#include "pclreader.h"

PCLReader::PCLReader()
{

}
QString PCLReader::pclFilePath() const{
    return PclFilePath_;
}
void PCLReader::setPclFilePath(QString pcl_file_path){
    std::cout << "get file path is " << pcl_file_path.toStdString() << std::endl;
    if(PclFilePath_ == pcl_file_path){
        return;
    }
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
    if(pcl_file_path.endsWith(".pcd", Qt::CaseInsensitive))
    {

        pcl::PCDReader reader;
        reader.read(pcl_file_path.toStdString(), *cloud);

        updateGeometry(cloud);

    }
}
void PCLReader::updateGeometry(pcl::PointCloud<pcl::PointXYZ>::Ptr & pcd_points){
    clear();
    QByteArray vertexData;
    unsigned int points_num =  pcd_points->points.size();
    vertexData.resize(sizeof(float) * 3 *points_num);
    float *p = reinterpret_cast<float *>(vertexData.data());
    for(auto pcd_point : *pcd_points){
        *p++ = pcd_point.x;
        *p++ = pcd_point.y;
        *p++ = pcd_point.z;
    }
    setVertexData(vertexData);
    setPrimitiveType(QQuick3DGeometry::PrimitiveType::Points);
    setStride(3 * sizeof(float));
    addAttribute(QQuick3DGeometry::Attribute::PositionSemantic,
                 0,
                 QQuick3DGeometry::Attribute::F32Type);

}
