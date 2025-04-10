#ifndef MUTE_MICROPHONE_H
#define MUTE_MICROPHONE_H

#include <napi.h>
#include <string>

void MuteMicrophone(Napi::Env env, Napi::Function muteFunction, Napi::Object instanceObj, const std::string &actionName);

#endif
