import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
  id: root
  visible: true
  width: 640
  height: 480
  title: qsTr("Keyboard monitor")

  /*
   * As mensioned in main.cpp file, you can simply acess the monitor
   * like standard item thanks to setting context before. Just use keyboardMonitor keyword.
   */

  Page {
    id: mainPage
    anchors.fill: parent

    Text {
      id: apsLabel

      anchors {
        top: parent.top
        left: parent.left
        leftMargin: 100
        topMargin: 40
      }

      font.pointSize: 20
      text: qsTr("APS")
    }

    Text {
      id: apsValue
      anchors {
        top: apsLabel.bottom
        topMargin: 10
        horizontalCenter: apsLabel.horizontalCenter
      }

      font.pointSize: 40
      /* By using Q_PROPERTY makro in class declaration
       * you are able to use property binding like with
       * standard object properties.
       */
      text: keyboardMonitor.aps
    }

    Text {
      id: apmLabel

      anchors {
        top: parent.top
        right: parent.right
        rightMargin: 100
        topMargin: 40
      }

      font.pointSize: 20
      text: qsTr("APM")
    }

    Text {
      id: apmValue

      anchors {
        top: apmLabel.bottom
        topMargin: 10
        horizontalCenter: apmLabel.horizontalCenter
      }
      visible: false
      font.pointSize: 40
      text: keyboardMonitor.apm
    }

    Text {
      id: avarageLabel

      anchors {
        top: apmValue.bottom
        topMargin: 10
        horizontalCenter: parent.horizontalCenter
      }

      font.pointSize: 20
      text: qsTr("Avarage APS")
    }

    Text {
      id: avarageValue
      anchors {
        top: avarageLabel.bottom
        topMargin: 10
        horizontalCenter: parent.horizontalCenter
      }
      visible: false
      font.pointSize: 30
      text: keyboardMonitor.avarageAps.toFixed(3)
    }

    Text {
      id: historyLabel
      anchors {
        top: avarageValue.bottom
        topMargin: 10
        horizontalCenter: parent.horizontalCenter
      }

      font.pointSize: 20
      text: qsTr("APM History")
    }

    Rectangle {
      id: historyWrapper
      width: mainPage.width * 0.8
      height: hisoryValue.height
      color: "#EBEBEB"
      radius: 10

      anchors {
        top: historyLabel.bottom
        topMargin: 10
        horizontalCenter: parent.horizontalCenter
      }

      border {
        color: "#404040"
        width: 1
      }

      Text {
        id: hisoryValue
        width: parent.width * 0.95
        anchors.centerIn: parent

        font.pointSize: 15
        horizontalAlignment: Text.AlignHCenter
        elide: Text.ElideLeft
        text: qsTr("Empty")
      }
    }

    /*
     * The monitor can also be manually stopped or started
     */
    Button {
      id: runningButton
      anchors {
        top: historyWrapper.bottom
        topMargin: 10
        horizontalCenter: parent.horizontalCenter
      }

      text: keyboardMonitor.isRunning? qsTr("STOP"): qsTr("START")

      onClicked: {
        keyboardMonitor.setIsRunning(!keyboardMonitor.isRunning)
      }
    }


    /*
     * All main monitor properties also have corresponding
     * signals. They can be connected with Connections object
     * like shown below.
     */
    Connections {
      target: keyboardMonitor

      onApmChanged: {
        if(!apmValue.visible) {
          apmValue.visible = true
        }
      }

      onAvarageApsChanged: {
        if(!avarageValue.visible) {
          avarageValue.visible = true
        }
      }

      onApmHistoryChanged: {
        hisoryValue.text = keyboardMonitor.apmHisoryStringify()
      }
    }
  }
}
