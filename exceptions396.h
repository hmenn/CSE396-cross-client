#ifndef EXCEPTIONS396_H
#define EXCEPTIONS396_H

#include <exception>
#include <QDebug>

using std::exception;

class InvalidConnectionException: public exception{
public:
    const char *what()const throw(){
        return "Connection error. Please check IP!";
    }
};

/*
// Another exception implementation: QException
class MyException : public QException
{
public:
    void raise() const { qDebug()<<"test"; throw *this; }
    MyException *clone() const { return new MyException(*this); }
};
*/
#endif // EXCEPTIONS396_H
