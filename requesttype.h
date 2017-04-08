#ifndef REQUESTTYPE_H
#define REQUESTTYPE_H

class RequestType{
  public:
    const static int OPEN_CONN=0;
    const static int CLOSE_CONN=1;
    const static int GET_COORDS=2;
    const static int GET_CURR_IMAGE=3;
    const static int UPDATE_COORDS=4;
};

#endif // REQUESTTYPE_H
