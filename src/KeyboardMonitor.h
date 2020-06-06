#ifndef KeyboardMonitor_H
#define KeyboardMonitor_H

#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QVector>

//Libraries neccecary for input tracking
#include <windows.h>
#include <winuser.h>

/*
 * This class is main component of the project. It uses windows libraries
 * to detrmine state of keyboard (and also mouse) buttons.
 * By using those libraries the keyboard state can also be tracked in the background.
 * User don't have to be focused on window for the tracking to take place - it can
 * eaven be minimalized.
 * The keys state are checked every time
 * the timer is triggered. Timer is triggered every 100ms.
 * User activity is measured with three variablem APS, APM and avarageAps.
 *
 *  -APS variable stands for Actions Per Second. It's number of buttons pressed by user every second.
 *  APS is updated every second.
 *
 *  -APM variable stands for Actions Per Minute. It's sum of the number of keys presses on the
 *  keyboard, per minute. As expected variable is updated every minute.
 *
 *  -AvarageAPS is just avarage number of actions per second. It is updated every minute.
 *  Avarage is counted simply by deviding current APM value by 60.
 *
 *  -ApmHistory is a vector containing all values of APM that were recorded
 *
 *  DISCLAIMER: Scythe-Studio does not bear responsibility for inappropriate or malicious use of code in this project
 */


class KeyboardMonitor : public QObject
{
    Q_OBJECT

    //Q_PROPERTY makro is used to make the variables visible to the QML
    Q_PROPERTY(unsigned int aps READ aps NOTIFY apsChanged)
    Q_PROPERTY(unsigned int apm READ apm NOTIFY apmChanged)
    Q_PROPERTY(float avarageAps READ avarageAps NOTIFY avarageApsChanged)
    Q_PROPERTY(QVector<unsigned int> apmHistory READ apmHistory NOTIFY apmHistoryChanged)

    /*
     * The isRunning property is created (not simply expose qTimer)
     * in order to make sure that property binding works
     */
    Q_PROPERTY(bool isRunning READ isRunning WRITE setIsRunning NOTIFY isRunningChanged)

public:
    explicit KeyboardMonitor(QObject *parent = nullptr);
    unsigned int aps() const;
    unsigned int apm() const;
    float avarageAps() const;
    bool isRunning() const;
    QVector<unsigned int> apmHistory() const;
    Q_INVOKABLE QString apmHisoryStringify() const;

public slots:
    void setIsRunning(bool isRunning);

private slots:
    void trackActions();
    void setAps(unsigned int aps);
    void setApm(unsigned int apm);
    void setAvarageAps(float avarageAps);
    void apsUpdate();
    void apmAndAvarageUpdate();

signals:
    void apsChanged(unsigned int aps);
    void apmChanged(unsigned int apm);
    void avarageApsChanged(float avarageAps);
    void isRunningChanged(bool isRunning);
    void apmHistoryChanged(QVector<unsigned int> apmHistory);

private:
    unsigned int _numberOfActions;
    unsigned int _numberOfActionsInMinute;

    const short _iterationsToApsUpdate;
    const short _iterationsToApmUpdate;

    short _secIterator;
    short _minIterator;

    unsigned int _aps;
    unsigned int _apm;
    float _avarageAps;

    bool _isRunning;
    QTimer *_timer;
    QVector<unsigned int> _apmHistory {};
};

#endif // KeyboardMonitor_H
