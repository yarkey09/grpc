#include "account_info.h"

#include <string>
using std::string;

yarkey::AccountInfo::AccountInfo(string account_id, string password, string name) {
  this->account_id = account_id;
  this->password = password;
  this->name = name;
}

yarkey::AccountInfo::~AccountInfo() {
}

string yarkey::AccountInfo::getAccountId() {
  return account_id;
}

string yarkey::AccountInfo::getPassword() {
  return password;
}

string yarkey::AccountInfo::getName() {
  return name;
}