/****************************************************************************
**
** Copyright (C) 2014 Kurt Pattyn <pattyn.kurt@gmail.com>.
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtWebSockets module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia. For licensing terms and
** conditions see http://qt.digia.com/licensing. For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights. These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/
#ifndef ECHOSERVER_H
#define ECHOSERVER_H

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QByteArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QVector>
#include <QtCore/QJsonArray>


QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

struct Point
{
    float x , y,z,a;
public:
    Point(float _x = 0,float _y = 0,float _z = 0,float _a = 0):
        x(_x),y(_y),z(_z),a(_a)
    {

    }

    QJsonObject toJsonObject()
    {
        QJsonObject obj;
        obj.insert("x",x) ;
        obj.insert("y",y) ;
        obj.insert("z",z) ;
        obj.insert("a",a) ;
        return obj;
    }
};

class PointCloudServer : public QObject
{
    Q_OBJECT
public:
    explicit PointCloudServer(quint16 port, bool debug = false, QObject *parent = Q_NULLPTR);
    ~PointCloudServer();

Q_SIGNALS:
    void closed();
    void newConnect();

private Q_SLOTS:
    void onNewConnection();
    void processTextMessage(QString message);
    void processBinaryMessage(QByteArray message);
    void socketDisconnected();
    void BoardcastMessage(QString message);
    static QJsonArray pointarray2json(QVector<Point> & data);
public Q_SLOTS:
    void BoardcastPointCloud(QVector<Point> & data);
private:
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
    bool m_debug;
};

#endif //ECHOSERVER_H
