import QtQuick 2.8
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.1

Rectangle {
    id: rectangle
    //width: 640
    //height: 280
    property alias column: column

    ColumnLayout {
        Layout.margins: 0
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        Column {
            id: column
            spacing: 3
            Layout.alignment: Qt.AlignHCenter

            Text {
                id: text1
                text: qsTr("gtarma-dl")
                font.bold: true
                font.family: "Arial"
                renderType: Text.NativeRendering
                font.pixelSize: 26
                //Layout.alignment: Qt.AlignHCenter
                //Layout.margins: 0
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
            }

            Text {
                id: text2
                text: qsTr("@sequoiia")
                font.bold: true
                font.family: "Arial"
                renderType: Text.NativeRendering
                font.pixelSize: 11
                //Layout.alignment: Qt.AlignHCenter
                //Layout.margins: 0
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
                bottomPadding: 15
            }

            ProgressBar {
                id: downloadProgressBar
//                objectName: downloadProgressBar
                value: progressData.progressvalue
            }

            Text {
                id: text3
                text: progressData.subtext
                font.bold: true
                font.family: "Arial"
                renderType: Text.NativeRendering
                font.pixelSize: 11
                //Layout.alignment: Qt.AlignHCenter
                //Layout.margins: 0
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
            }

        }
    }
}
