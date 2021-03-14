#ifndef DRONEDATAPOINT_H
#define DRONEDATAPOINT_H

#include <QObject>

class DroneDataPoint : public QObject
{
    Q_OBJECT
public:
    explicit DroneDataPoint(QObject *parent = nullptr);

signals:

};

#endif // DRONEDATAPOINT_H
