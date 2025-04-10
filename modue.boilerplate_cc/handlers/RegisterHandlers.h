#ifndef REGISTER_HANDLERS_H
#define REGISTER_HANDLERS_H

#include <napi.h>
#include <string>

std::string RegisterOnInitializeHandler(Napi::Value instance);
std::string RegisterOnInitializeHandlerLed(Napi::Value instance);
std::string RegisterOnConfigurationChangeHandler(Napi::Value instance, Napi::Value configuration);
std::string RegisterResourceHandler(Napi::Value instance, Napi::Value resources);
std::string RegisterOnKeyDownHandler(Napi::Value instance);
std::string RegisterOnKeyDownAppsListHandler(Napi::Value instance);
std::string RegisterOnKeyDownAudioAppsListHandler(Napi::Value instance);
std::string RegisterOnKeyDownSpeakersListHandler(Napi::Value instance);
std::string RegisterOnKeyDownMicrophonesListHandler(Napi::Value instance);
std::string RegisterOnKeyUpHandler(Napi::Value instance);
std::string RegisterOnDeactivateHandler(Napi::String id);
std::string RegisterVolumeOnChangeHandler(Napi::Value instance, Napi::Number value);
std::string RegisterOnChangeHandler(Napi::Value instance, Napi::Number value);
std::string RegisterSwitchOnChangeHandler(Napi::Value instance, Napi::Value value);
std::string UseSystemVolumeHandler(Napi::Value instance, Napi::Number value);
std::string UseMicrophoneSystemVolumeHandler(Napi::Value instance, Napi::Number value);
std::string RegisterAppsOrDeviceList(Napi::Value instance, Napi::Value collection);
std::string RegisterMuteUnmuteOnKeyDownHandler(Napi::Value instance);
std::string RegisterMicrophoneVolumeOnChangeHandler(Napi::Value instance, Napi::Number value);
std::string RegisterTakeScreenshotHandler(Napi::Value instance);
std::string RegisterControlSystemMediaPlayerHandler(Napi::Value instance);
std::string RegisterOpenChromeAppHandler(Napi::Value instance);
std::string RegisterPressKeystrokesHandler(Napi::Value instance);
std::string Notify();

#endif
