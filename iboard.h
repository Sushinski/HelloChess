#ifndef IBOARD_H
#define IBOARD_H

class IBoard
{
public:
    IBoard();
    virtual void createBoard()= 0;
    virtual void writeLog() = 0;
    virtual void getLogRecord() const = 0;
    virtual ~IBoard(){}
};

#endif // IBOARD_H
