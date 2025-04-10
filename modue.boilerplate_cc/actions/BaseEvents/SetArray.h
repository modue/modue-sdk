#ifndef SETARRAY_H
#define SETARRAY_H

#include <napi.h>
#include <string>
#include <vector>

void SetArray(Napi::Env env, Napi::Function setFunction, Napi::Object instanceObj, const std::string &actionName, const std::vector<std::string> &ledsToFlash);

#endif
