import QtQuick
import PCDReader 1.0
import QtQuick3D 6
import QtQuick3D.Helpers
Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    MouseArea{
        id:mouseArea
        anchors.fill: parent
        acceptedButtons:  Qt.AllButtons
        onPressed: {
            console.log(mouseX)
        }

        onWheel: {
            if(wheel.angleDelta.y > 0 && mainCamera.z < 200){

                mainCamera.z += 15
            }
            else if(wheel.angleDelta.y < 0 && mainCamera.z > 20){
                mainCamera.z -= 15
            }
        }
    }

    View3D {
        anchors.fill: parent
        Node {
            id: sceneRoot
            PerspectiveCamera {
                id: mainCamera
                z: 30
            }
            DirectionalLight {
                position: Qt.vector3d(0, 0, 400)
                color: "white"
                ambientColor: Qt.rgba(0.1, 0.1, 0.1, 1.0)
            }
            Model {
                scale: Qt.vector3d(10, 10, 10)
                geometry: GridGeometry {
                    horizontalLines: 1000
                    verticalLines: 1000
                }
                materials: [ DefaultMaterial { } ]
            }
            Model {
                source: "#Cube"
                z:-10
                scale: Qt.vector3d(10, 10, 0.1)
                materials: [
                    DefaultMaterial {
                        diffuseColor: "silver"
                    }
                ]
            }

            Model {
                id:pcd_model
                z:0
                geometry: PCDReader {
                    pclFilePath: "Data/map.pcd"
                }
                materials: [
                    DefaultMaterial {
                        diffuseColor: "black"
                        lighting: DefaultMaterial.NoLighting
                        pointSize:0.1
                        diffuseLightWrap:10
                    }
                ]

            }


        }
    }

    WasdController {
        controlledObject: mainCamera
    }
}

