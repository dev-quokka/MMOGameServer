#pragma once

#include "Define.h"
#include "ConnUser.h"
#include "RedisManager.h"
#include "MySQLManager.h"

#include <atomic>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <deque>
#include <queue>

#pragma comment(lib, "ws2_32.lib") // 소켓 프로그래밍용
#pragma comment(lib, "mswsock.lib") // AcceptEx 사용용

class QuokkaServer {
public:
    QuokkaServer();
    ~QuokkaServer();

    bool init(const UINT16 MaxThreadCnt_, int port_);
    bool StartWork(UINT32 maxClientCount_);

private:
    bool CreateWorkThread();
    bool CreateRedisThread();
    bool CreateAccepterThread();

    void WorkThread(); // IOCP Complete Event Thread
    void RedisThread(); // Redis req Thread
    void AccepterThread(); // Accept req Thread

    ConnUser* GetClientInfo(TaskType taskType);
    void CloseSocket(ConnUser* connUser, bool isForce_ = false);
    void OnConnect(const UINT32 clientIndex_);
    void OnReceive(const UINT32 clientIndex_, const DWORD size_, char* pData_);

private:
    // 1 bytes
    bool WorkRun = true;
    bool AccepterRun = true;
    std::atomic<bool> UserMaxCheck = false;

    // 2 bytes
    UINT16 MaxThreadCnt = 0;

    // 4 bytes
    UINT32 maxClientCount = 0;
    std::atomic<int> UserCnt = 0;

    // 8 bytes
    SOCKET ServerSKT = INVALID_SOCKET;
    HANDLE sIOCPHandle = INVALID_HANDLE_VALUE;
    std::unique_ptr<RedisManager> p_RedisManager;
    std::unique_ptr<MySQLManager> p_MySQLManager;

    // 16 bytes
    std::thread AcceptThread;

    // 32 bytes
    std::vector<std::thread> WorkThreads;
    std::vector<std::unique_ptr<ConnUser>> ConnUsers; // Connetion User List

    // 40 bytes
    std::queue<SOCKET> SocketPool; // Socket Pool For Waitting User

    std::queue<SOCKET> WaittingQueue; // Waitting User List

    // 80 bytes
    std::mutex usercnt_mutex;
};
