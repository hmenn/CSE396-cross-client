#ifndef EXCEPTIONS396_H
#define EXCEPTIONS396_H


class InvalidConnectionException: public QException{
public:
    void raise() {throw *this;}
    InvalidConnectionException *clone() const{return new InvalidConnectionException(*this);}
};

#endif // EXCEPTIONS396_H
