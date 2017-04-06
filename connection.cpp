#include "requirements.h"
#include "connection.h"

using namespace std;

Connection::Connection(QString ip, QString port) throw (InvalidConnectionException)
{
    std::cout<<"Connection opened"<<std::endl;
}


void Connection::sendRequest(QString message) throw (exception){

}
