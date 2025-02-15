#pragma once
#include "InGameUser.h"

#include <vector>
#include <string>
#include <cstdint>
#include <ws2tcpip.h>
#include <utility>
#include <iostream>

class InGameUserManager {
public:
	~InGameUserManager() {
		for (int i = 0; i < inGmaeUsers.size(); i++) {
			delete inGmaeUsers[i];
		}
	}

	void Init(uint16_t maxClientCount_);
	InGameUser* GetInGameUserByObjNum(uint16_t connObjNum_);
	void Set(uint16_t connObjNum_, std::string userToken_, std::string userId_, uint32_t userPk_, unsigned int userExp_, uint16_t userLevel_);
	void Reset(uint16_t connObjNum_);

private:
	std::vector<InGameUser*> inGmaeUsers;
	std::vector<short> expLimit = { 1,1,2,3,5,8,13,21,34,56,90,146,236,382,618,1000 };
};