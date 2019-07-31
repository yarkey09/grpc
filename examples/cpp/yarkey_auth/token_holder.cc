#include "token_holder.h"

#include <string>
using std::string;

yarkey::TokenHolder::TokenHolder(string account_id, string device_id, string token) {
  this->account_id = account_id;
  this->device_id = device_id;
  this->token = token;
}

yarkey::TokenHolder::~TokenHolder() {
}

string yarkey::TokenHolder::getAccountId() {
  return account_id;
}

string yarkey::TokenHolder::getDeviceId() {
  return device_id;
}

string yarkey::TokenHolder::getToken() {
  return token;
}