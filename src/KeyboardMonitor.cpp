#include "KeyboardMonitor.h"

KeyboardMonitor::KeyboardMonitor(QObject *parent)
    : QObject(parent)
    , _numberOfActions(0) //variables initialization
    , _numberOfActionsInMinute(0)
    , _iterationsToApsUpdate(9)
    , _iterationsToApmUpdate(60)
    , _secIterator(0)
    , _minIterator(0)
    , _aps(0)
    , _apm(0)
    , _avarageAps(0)
    , _timer(new QTimer(this)) //timer object initialization
{
    //Connecting timer to function that handles keboard tracking
    connect(_timer, &QTimer::timeout, this, &KeyboardMonitor::trackActions);

    _timer->setInterval(100);
    setIsRunning(true);
}

//####################### Getters and setters #################################

unsigned int KeyboardMonitor::aps() const
{
    return _aps;
}

unsigned int KeyboardMonitor::apm() const
{
    return _apm;
}

float KeyboardMonitor::avarageAps() const
{
    return _avarageAps;
}

bool KeyboardMonitor::isRunning() const
{
    return _isRunning;
}

QString KeyboardMonitor::apmHisoryStringify() const
{
    QString ampHistoryStringify;
    for (auto number : _apmHistory) {
        ampHistoryStringify.append(QString::number(number) + " ");
    }
    return ampHistoryStringify;
}

QVector<unsigned int> KeyboardMonitor::apmHistory() const
{
    return _apmHistory;
}

void KeyboardMonitor::setIsRunning(bool isRunning)
{
    if (_isRunning == isRunning) {
        return;
    }

    _isRunning = isRunning;

    //If is running is changed the
    if(_isRunning != _timer->isActive()) {
        if(_isRunning) {
            _timer->start();
        }
        else {
            _timer->stop();
        }
    }
    emit isRunningChanged(_isRunning);
}


void KeyboardMonitor::setAps(unsigned int aps)
{
    if (_aps == aps) {
        return;
    }

    _aps = aps;
    emit apsChanged(_aps);
}

void KeyboardMonitor::setApm(unsigned int apm)
{
    if (_apm == apm) {
        return;
    }

    _apm = apm;
    emit apmChanged(_apm);
}

void KeyboardMonitor::setAvarageAps(float avarageAps)
{
    if (qFuzzyCompare(_avarageAps, avarageAps)) {
        return;
    }

    _avarageAps = avarageAps;
    emit avarageApsChanged(_avarageAps);
}

//####################### Tracking functions #################################

void KeyboardMonitor::apsUpdate()
{
    _secIterator = 0;
    _numberOfActionsInMinute += _numberOfActions;

    setAps(_numberOfActions);
    _numberOfActions = 0;

    _minIterator++;
}
void KeyboardMonitor::apmAndAvarageUpdate()
{
    _minIterator = 0;
    setApm(_numberOfActionsInMinute);

    //Updating apmHistory and emiting signal due to its change
    _apmHistory.append(_numberOfActionsInMinute);
    emit apmHistoryChanged(_apmHistory);

    setAvarageAps((float)_numberOfActionsInMinute/60.0);
    _numberOfActionsInMinute = 0;
}


void KeyboardMonitor::trackActions()
{
    //Loop through all keys state
    for (int i = 1; i < 255; ++i) {
        //Avoiding double counting by general key codes (like alt without side implication)
        if((i < 16 || i > 18) && i!= 165) {
            //Most significant bit tells if the key is pressed
            if(GetAsyncKeyState(i) & 0x100000) {
                //If the button is pressed number of action is increased
                _numberOfActions++;
                qDebug() << i;
            }
        }
    }

    _secIterator++;

    /* Every second passed the aps variable is updated
     * We're using iterators to determine time passed, because
     * we want to keep the code as simple as possible.
     * Istead of iterators multiple timers could be used, but they
     * are working on seperate threads and in this
     * case some synchronization mechanism (like mutex) would be
     * needed.
     */
    if(_secIterator == _iterationsToApsUpdate) {
        apsUpdate();

        if(_minIterator == _iterationsToApmUpdate) {
            apmAndAvarageUpdate();
        }
    }
}
