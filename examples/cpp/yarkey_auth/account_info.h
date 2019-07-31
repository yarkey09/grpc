#pragma once

#include <string>
using std::string;

namespace yarkey {

class AccountInfo {
public:
    AccountInfo(string account_id, string password, string name);
    virtual ~AccountInfo();

    string getAccountId();
    string getPassword();
    string getName();

private:
    string account_id;
    string password;
    string name;
};

typedef AccountInfo * AccountInfoRef;

} // namespace yarkey