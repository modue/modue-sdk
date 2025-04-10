#ifndef UNMUTE_MICROPHONE_H
#define UNMUTE_MICROPHONE_H

#include <napi.h>
#include <string>

void UnmuteMicrophone(Napi::Env env, Napi::Function unmuteFunction, Napi::Object instanceObj, const std::string &actionName);

#endif
