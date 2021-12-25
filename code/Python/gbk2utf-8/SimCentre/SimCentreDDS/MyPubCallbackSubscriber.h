#ifndef MyPubCallbackSubscriber_h__
#define MyPubCallbackSubscriber_h__

#include <QObject>
#include <QThread>
#include <QMutex>
#include "SimMessageDDs.h"
#include "MapSet.h"


void SubscriberCallback(SimMessageDDs dds);
#endif // MyPubCallbackSubscriber_h__


