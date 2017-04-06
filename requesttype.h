#ifndef REQUESTTYPE_H
#define REQUESTTYPE_H


class RequestType{
  public:
    const int OPEN_CONN=0;
    const int CLOSE_CONN=1;
    const int GET_COORDS=2;
    const int GET_CURR_IMAGE=3;
    const int UPDATE_COORDS=4;
};

#endif // REQUESTTYPE_H
