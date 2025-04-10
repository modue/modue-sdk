#ifndef UPDATESETSYSTEMVOLUME_H
#define UPDATESETSYSTEMVOLUME_H

#include <napi.h>
#include <string>

void SetSystemVolume(Napi::Env env, Napi::Function setFunction, Napi::Object instanceObj, Napi::Number volume, const std::string &deviceType = "", const std::string &deviceId = "");

#endif
