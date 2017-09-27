import QtQuick 2.6
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 280
    maximumHeight: 280
    minimumHeight: 280
    minimumWidth: 640
    maximumWidth: 640
    title: qsTr("gtarma-dl")

    MainForm {
        anchors.fill: parent
        /*
        mouseArea.onClicked: {
            console.log(qsTr('Clicked on background. Text: "' + textEdit.text + '"'))
        }
        */
    }
}
