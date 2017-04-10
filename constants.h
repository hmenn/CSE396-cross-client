#ifndef CONSTANTS_H
#define CONSTANTS_H

class Constants{
public:
    class RequestTypes{
    public:
        static const int OPEN_CONNECTION=1;
        static const int CLOSE_CONNECTION=2;
        static const int ASK_CURRENT_IMAGE=3;
        static const int ASK_CURRENT_COORDS=4;
        static const int UPDATE_COORDS=5;
    };

    static const int PORT=3965;
};

#endif // CONSTANTS_H
