#pragma once

#include <string>
using std::string;

namespace yarkey {

class TokenHolder {
public:
    TokenHolder(string account_id, string device_id, string token);
    ~TokenHolder();

    string getAccountId();
    string getDeviceId();
    string getToken();

private:
    string account_id;
    string device_id;
    string token;
};

typedef TokenHolder * TokenHolderRef;
}