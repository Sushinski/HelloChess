#ifndef LOGGER_H
#define LOGGER_H


class Logger
{
public:
    Logger();
    ~Logger();
    void write(const QSize& from , const QSize& to);
    void read(int turn);
};

#endif // LOGGER_H
