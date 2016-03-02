#include "server.h"

server::server(int nPort, QObject *parent):  QTcpServer(parent), m_nNextBlockSize(0)
{    
    m_ptcpServer = new QTcpServer(this);
    if (m_ptcpServer->listen(QHostAddress::Any, nPort))
    {
        qDebug() << "Server able to listen.";
    }
    if (m_ptcpServer->isListening())
    {
        qDebug() << "Server is listening on port:" << QString::number(m_ptcpServer->serverPort());
    }
    else
    {
        qDebug() << "Server is not able to listen. It seemed like port already use.";
    }

    CreatorConnections();
}

server::~server()
{
    qDebug() << "Destructor Server::~Server";
}

void server::slotNewConnection()
{
    pClientSocket = m_ptcpServer->nextPendingConnection();
    qDebug() << "New client from:" << pClientSocket->peerAddress().toString();

    connect(pClientSocket, SIGNAL(disconnected()), pClientSocket, SLOT(deleteLater()));
    connect(pClientSocket, SIGNAL(readyRead()), this, SLOT(slotReadClient()) );
}

void server::CreatorConnections()
{
    connect(m_ptcpServer, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));
}

void server::slotReadClient()
{
    //qDebug() << "TSPServer::slotReadClient()";

    QDataStream in(pClientSocket);
    in.setVersion(QDataStream::Qt_5_4);
    for (;;)
    {
        if (!m_nNextBlockSize)
        {
            if (pClientSocket->bytesAvailable() < sizeof(quint16))
            {
                break;
            }
            in >> m_nNextBlockSize;
        }

        if (pClientSocket->bytesAvailable() < m_nNextBlockSize)
        {
            break;
        }


        QString json_document;
        in >> json_document;


        QFile jsonFile("/home/kopylov/received.json");
        jsonFile.open(QFile::Append);
        QTextStream out(&jsonFile);
        out << json_document;
        jsonFile.close();

        qDebug() << "Server Received:" << json_document;

        m_nNextBlockSize = 0;
    }
}

