project(pcl_reader)

add_library(pcl_reader STATIC
    pclreader.h pclreader.cpp)
target_link_libraries(pcl_reader
    PRIVATE
    Qt6::Quick
    Qt6::Quick3D
    ${PCL_LIBRARIES}
)
