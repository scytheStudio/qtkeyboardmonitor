# QtKeyboardMonitor
App written with Qt to track keyboard usage on Windows.

It uses windows libraries to detrmine state of keyboard (and also mouse) buttons.
By using those libraries the keyboard state can also be tracked in the background.
User don't have to be focused on window for the tracking to take place - it can eaven be minimalized.
The keys state are checked every time the timer is triggered. Timer is triggered every 100ms.
User activity is measured with three variablem APS, APM and avarageAps.

- APS variable stands for Actions Per Second. It's number of buttons pressed by user every second. APS is updated every second.
- APM variable stands for Actions Per Minute. It's sum of the number of keys presses on the keyboard, per minute. As expected variable is updated every minute.
- AvarageAPS is just avarage number of actions per second. It is updated every minute. Avarage is counted simply by deviding current APM value by 60.

# How to use
To see the example simply clone this repository and simply run the project - no additional configuration is needed.

If you want to reuse this code in a QML app, simply create proper C++ class with code from KeyboardMonitor.cpp and KeyboardMonitor.h and then, add context to QML engine with this line:

`engine.rootContext()->setContextProperty("keyboardMonitor", keyboardMonitor);`

Now you can use keyboard monitor from the QML level. For examples how to use it, see main.qml file.

# Licence
This project is licensed under the MIT License - see the LICENSE.txt file for details.
 
 DISCLAIMER: Scythe-Studio does not bear responsibility for inappropriate or malicious use of code in this project
