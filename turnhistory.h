#ifndef TURNHISTORY_H
#define TURNHISTORY_H
#include <QString>
#include <QSharedPointer>
#include <QFile>
#include <QTextStream>

class TurnHistory : public QObject
{
    Q_OBJECT
public:
    explicit TurnHistory(QString filename = "turn_history", QObject *parent = 0);
    bool openHistFile();
    void writeTurn(const QString& turn);
    QString readTurn( bool bFwd = true );
    ~TurnHistory();
private:
    QSharedPointer<QFile> m_file;
    QSharedPointer<QTextStream> m_stream;
    QList<QString> m_turn_buf;
    int m_cur_elem;
signals:
public slots:
};

#endif // TURNHISTORY_H
