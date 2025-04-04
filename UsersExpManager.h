#pragma once
#include <vector>
#include <ws2tcpip.h>
#include <utility>

struct EXP_MANAGER {
	uint8_t currentLevel;
	unsigned int currentExp;
};

class UsersExpManager {
public:
	void Init(UINT16 maxClientCount_);
	uint8_t GetLevel(UINT16 connObjNum_);
	std::pair<uint8_t, unsigned int> ExpUp(UINT16 connObjNum_, short mobExp_);
	void Set(UINT16 connObjNum_, uint8_t currentLevel_, unsigned int currentExp_);
	void Reset(UINT16 connObjNum_);

private:
	std::vector<EXP_MANAGER*> inGmaeUser;
	std::vector<short> enhanceProbabilities = { 0,1,2,3,5,8,13,21,34,56,90,146,236,382,618,1000 };
};

