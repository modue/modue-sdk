#ifndef UPDATESETHANDLER_H
#define UPDATESETHANDLER_H

#include <napi.h>
#include <string>

void Set(Napi::Env env, Napi::Function setFunction, Napi::Object instanceObj, double value, const std::string &actionName);

#endif
