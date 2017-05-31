#ifndef REQUIREMENTS_H
#define REQUIREMENTS_H

#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <QString>
#include <QException>
#include "exceptions396.h"
#include "constants.h"
#include <string>
#include <math.h>

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")



#endif // REQUIREMENTS_H
