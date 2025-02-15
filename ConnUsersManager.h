#pragma once

#include <winsock2.h>
#include <iostream>
#include <tbb/concurrent_hash_map.h>

#include "ConnUser.h"

class ConnUsersManager {
public:
    ~ConnUsersManager() {
        for (auto iter = ConnUsers.begin(); iter != ConnUsers.end(); iter++) {
            delete iter->second;
        }
    }

    void InsertUser(SOCKET TempSkt_); // Init ConnUsers
    void DeleteUser(SOCKET TempSkt_);
    ConnUser* FindUser(SOCKET UserSkt_);

private:
    // 576 bytes
    tbb::concurrent_hash_map<SOCKET, ConnUser*> ConnUsers; // ConnUsers Info
};
