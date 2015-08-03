#include "turnhistory.h"

TurnHistory::TurnHistory(QString filename, QObject *parent) : QObject(parent), m_file(new QFile(filename))
{
}

TurnHistory::~TurnHistory()
{
    if(m_file->isOpen())
        m_file->close();
}

bool TurnHistory::openHistFile()
{
    if(m_file->open( QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text | QIODevice::Unbuffered ))
    {
        m_stream = QSharedPointer<QTextStream>( new QTextStream(m_file.data()));
        return true;
    }
    return false;
}

void TurnHistory::writeTurn( const QString& turn )
{
    *m_stream << turn << '\n';
}

QString TurnHistory::readTurn( bool bFwd )
{
    QString turn;
    if( bFwd )
    {
        if(m_cur_elem < m_turn_buf.size())
            turn = m_turn_buf.at(m_cur_elem++);
        else
        {
            if( m_stream->readLineInto(&turn))
            {
                m_turn_buf.append(turn);
                m_cur_elem++;
            }
            else
                turn = "";
        }
    }
    else
    {
        if(m_cur_elem > 0)
            turn = m_turn_buf.at(m_cur_elem--);
        else
            turn = "";
    }
    return turn;
}
