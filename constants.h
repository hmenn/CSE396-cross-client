#ifndef CONSTANTS_H
#define CONSTANTS_H

#define PI 3.141592
class Constants{
public:
    /* Request */
    static const int REQ_OPEN_CONNECTION=1;
    static const int REQ_CLOSE_CONNECTION=2;
    static const int REQ_ASK_CURRENT_IMAGE=3;
    static const int REQ_ASK_CURRENT_COORDS=4;
    static const int REQ_UPDATE_COORDS=5;
    static const int REQ_CHANGE_MODE=6;

    /* Messages */
    static const char DELIMITER=',';

    /*Connection*/
    static const int PORT=3965;

    static const int MIN_BUFFER_SIZE=50;
};

#endif // CONSTANTS_H
