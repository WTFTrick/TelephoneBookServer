#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtNetwork>

#include <stdlib.h>


class server: public QTcpServer
{

    Q_OBJECT
private:
    QTcpServer* m_ptcpServer;
    quint16     m_nNextBlockSize;

private:
    void CreatorConnections();
    QTcpSocket* pClientSocket;

public slots:
    virtual void slotNewConnection();
    void slotReadClient   ();


public:
    server(int nPort, QObject *parent=0);
    ~server();
};

#endif // SERVER_H
