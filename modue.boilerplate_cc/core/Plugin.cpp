#include "Plugin.h"
#include "GUIDGenerator.h"
#include "./../handlers/RegisterHandlers.h"
#include "./../widget/WidgetActions.h"
#include "./../core/ActionWrapper.h"
#include "./../utils/FileLogger.h"
#include <unordered_map>

Napi::Object Plugin::Init(Napi::Env env, Napi::Object exports)
{
  Napi::Function func = DefineClass(env, "Plugin", {InstanceMethod("getConfiguration", &Plugin::GetConfiguration), Plugin::InstanceMethod("invokeAction", &Plugin::InvokeAction)});

  exports.Set("Plugin", func);
  return exports;
}

Plugin::Plugin(const Napi::CallbackInfo &info) : Napi::ObjectWrap<Plugin>(info)
{
  this->RegisterSlider("Basic - slider change event",
                       {{ActionToString(KeyActions::RegisterOnInitializeHandler), ActionWrapper(SingleParamHandler(RegisterOnInitializeHandler))},
                        {ActionToString(SliderActions::RegisterOnChangeHandler), ActionWrapper(ChangeHandler(RegisterOnChangeHandler))},
                        {ActionToString(SystemActions::UseSystemVolume), ActionWrapper(ChangeHandler(UseSystemVolumeHandler))}});

  this->RegisterKey("Basic - key change even",
                    {{ActionToString(KeyActions::RegisterOnInitializeHandler), ActionWrapper(SingleParamHandler(RegisterOnInitializeHandler))},
                     {ActionToString(KeyActions::RegisterOnKeyDownHandler), ActionWrapper(SingleParamHandler(RegisterOnKeyDownHandler))},
                     {ActionToString(KeyActions::RegisterOnKeyUpHandler), ActionWrapper(SingleParamHandler(RegisterOnKeyUpHandler))},
                     {ActionToString(KeyActions::RegisterOnDeactivateHandler), ActionWrapper(DeactivateHandler(RegisterOnDeactivateHandler))}});

  this->RegisterKnob("Basic - knob change event",
                     {{ActionToString(KnobActions::RegisterOnInitializeHandler), ActionWrapper(SingleParamHandler(RegisterOnInitializeHandler))},
                      {ActionToString(KnobActions::RegisterOnChangeHandler), ActionWrapper(ChangeHandler(RegisterOnChangeHandler))},
                      {ActionToString(KnobActions::RegisterOnDeactivateHandler), ActionWrapper(DeactivateHandler(RegisterOnDeactivateHandler))}});

  this->RegisterLedCluster("Basic - led init event",
                           {{ActionToString(LedClusterActions::RegisterOnInitializeHandler), ActionWrapper(SingleParamHandler(RegisterOnInitializeHandlerLed))},
                            {ActionToString(LedClusterActions::RegisterOnDeactivateHandler), ActionWrapper(DeactivateHandler(RegisterOnDeactivateHandler))}});

  this->RegisterKey("Basic - configuration & settings",
                    {{ActionToString(KeyActions::RegisterOnInitializeHandler), ActionWrapper(SingleParamHandler(RegisterOnInitializeHandler))},
                     {ActionToString(KeyActions::RegisterOnConfigurationChangeHandler), ActionWrapper(InitializeHandler(RegisterOnConfigurationChangeHandler))},
                     {ActionToString(ConfigurationActions::AddInput), ActionWrapper(ConfigurationMetadata{"config1", "Example string value", "An example input field", "string"})},
                     {ActionToString(ConfigurationActions::AddInput), ActionWrapper(ConfigurationMetadata{"config2", "Example string value2", "An example input2 field", "number"})},
                     {ActionToString(KeyActions::RegisterOnDeactivateHandler), ActionWrapper(DeactivateHandler(RegisterOnDeactivateHandler))}});

  this->RegisterKey("System - installed apps",
                    {{ActionToString(KeyActions::RegisterOnInitializeHandler), ActionWrapper(SingleParamHandler(RegisterOnInitializeHandler))},
                     {ActionToString(KeyActions::RegisterOnConfigurationChangeHandler), ActionWrapper(InitializeHandler(RegisterOnConfigurationChangeHandler))},
                     {ActionToString(SystemActions::UseSystemInstalledApps), ActionWrapper(InitializeHandler(RegisterAppsOrDeviceList))},
                     {ActionToString(KeyActions::RegisterOnKeyDownHandler), ActionWrapper(SingleParamHandler(RegisterOnKeyDownAppsListHandler))},
                     {ActionToString(KeyActions::RegisterOnDeactivateHandler), ActionWrapper(DeactivateHandler(RegisterOnDeactivateHandler))}});

  this->RegisterKey("System - audio apps",
                    {{ActionToString(KeyActions::RegisterOnInitializeHandler), ActionWrapper(SingleParamHandler(RegisterOnInitializeHandler))},
                     {ActionToString(KeyActions::RegisterOnConfigurationChangeHandler), ActionWrapper(InitializeHandler(RegisterOnConfigurationChangeHandler))},
                     {ActionToString(SystemActions::UseAudioApps), ActionWrapper(InitializeHandler(RegisterAppsOrDeviceList))},
                     {ActionToString(KeyActions::RegisterOnKeyDownHandler), ActionWrapper(SingleParamHandler(RegisterOnKeyDownAudioAppsListHandler))},
                     {ActionToString(KeyActions::RegisterOnDeactivateHandler), ActionWrapper(DeactivateHandler(RegisterOnDeactivateHandler))}});

  this->RegisterKey("System - available microphone devices",
                    {{ActionToString(KeyActions::RegisterOnInitializeHandler), ActionWrapper(SingleParamHandler(RegisterOnInitializeHandler))},
                     {ActionToString(KeyActions::RegisterOnConfigurationChangeHandler), ActionWrapper(InitializeHandler(RegisterOnConfigurationChangeHandler))},
                     {ActionToString(SystemActions::UseSystemAvailableMicrophoneDevices), ActionWrapper(InitializeHandler(RegisterAppsOrDeviceList))},
                     {ActionToString(KeyActions::RegisterOnKeyDownHandler), ActionWrapper(SingleParamHandler(RegisterOnKeyDownMicrophonesListHandler))},
                     {ActionToString(KeyActions::RegisterOnDeactivateHandler), ActionWrapper(DeactivateHandler(RegisterOnDeactivateHandler))}});

  this->RegisterKey("System - available speakers",
                    {{ActionToString(KeyActions::RegisterOnInitializeHandler), ActionWrapper(SingleParamHandler(RegisterOnInitializeHandler))},
                     {ActionToString(KeyActions::RegisterOnConfigurationChangeHandler), ActionWrapper(InitializeHandler(RegisterOnConfigurationChangeHandler))},
                     {ActionToString(SystemActions::UseSystemAvailableDevices), ActionWrapper(InitializeHandler(RegisterAppsOrDeviceList))},
                     {ActionToString(KeyActions::RegisterOnKeyDownHandler), ActionWrapper(SingleParamHandler(RegisterOnKeyDownSpeakersListHandler))},
                     {ActionToString(KeyActions::RegisterOnDeactivateHandler), ActionWrapper(DeactivateHandler(RegisterOnDeactivateHandler))}});

  this->RegisterSlider("System API - speaker volume",
                       {{ActionToString(KeyActions::RegisterOnInitializeHandler), ActionWrapper(SingleParamHandler(RegisterOnInitializeHandler))},
                        {ActionToString(SliderActions::RegisterOnChangeHandler), ActionWrapper(ChangeHandler(RegisterVolumeOnChangeHandler))},
                        {ActionToString(SystemActions::UseSystemVolume), ActionWrapper(ChangeHandler(UseSystemVolumeHandler))},
                        {ActionToString(KeyActions::RegisterOnDeactivateHandler), ActionWrapper(DeactivateHandler(RegisterOnDeactivateHandler))}});

  this->RegisterKey("System API - microphone mute/unmute",
                    {{ActionToString(KeyActions::RegisterOnInitializeHandler), ActionWrapper(SingleParamHandler(RegisterOnInitializeHandler))},
                     {ActionToString(KeyActions::RegisterOnKeyDownHandler), ActionWrapper(SingleParamHandler(RegisterMuteUnmuteOnKeyDownHandler))},
                     {ActionToString(KeyActions::RegisterOnConfigurationChangeHandler), ActionWrapper(InitializeHandler(RegisterOnConfigurationChangeHandler))},
                     {ActionToString(SystemActions::UseSystemMuteMicrophone), ActionWrapper(NotificationHandler(Notify))},
                     {ActionToString(SystemActions::UseSystemUnmuteMicrophone), ActionWrapper(NotificationHandler(Notify))},
                     {ActionToString(KeyActions::RegisterOnDeactivateHandler), ActionWrapper(DeactivateHandler(RegisterOnDeactivateHandler))}});

  this->RegisterSlider("System API - microphone volume",
                       {{ActionToString(KeyActions::RegisterOnInitializeHandler), ActionWrapper(SingleParamHandler(RegisterOnInitializeHandler))},
                        {ActionToString(SliderActions::RegisterOnChangeHandler), ActionWrapper(ChangeHandler(RegisterMicrophoneVolumeOnChangeHandler))},
                        {ActionToString(SystemActions::UseSystemVolume), ActionWrapper(NotificationHandler(Notify))},
                        {ActionToString(SystemActions::UseMicrophoneSystemVolume), ActionWrapper(ChangeHandler(UseSystemVolumeHandler))},
                        {ActionToString(KeyActions::RegisterOnDeactivateHandler), ActionWrapper(DeactivateHandler(RegisterOnDeactivateHandler))}});

  this->RegisterLedCluster("Resource monitoring on Led",
                           {{ActionToString(LedClusterActions::RegisterOnInitializeHandler), ActionWrapper(SingleParamHandler(RegisterOnInitializeHandlerLed))},
                            {ActionToString(SystemActions::UseSystemMonitorResources), ActionWrapper(InitializeHandler(RegisterResourceHandler))},
                            {ActionToString(LedClusterActions::RegisterOnDeactivateHandler), ActionWrapper(DeactivateHandler(RegisterOnDeactivateHandler))}});

  this->RegisterKey("System API - screenshot",
                    {{ActionToString(KeyActions::RegisterOnInitializeHandler), ActionWrapper(SingleParamHandler(RegisterOnInitializeHandler))},
                     {ActionToString(KeyActions::RegisterOnConfigurationChangeHandler), ActionWrapper(InitializeHandler(RegisterOnConfigurationChangeHandler))},
                     {ActionToString(KeyActions::RegisterOnKeyDownHandler), ActionWrapper(SingleParamHandler(RegisterTakeScreenshotHandler))},
                     {ActionToString(SystemActions::UseSystemTakeScreenshot), ActionWrapper(NotificationHandler(Notify))},
                     {ActionToString(KeyActions::RegisterOnDeactivateHandler), ActionWrapper(DeactivateHandler(RegisterOnDeactivateHandler))}});

  this->RegisterKey("System API - media player",
                    {{ActionToString(KeyActions::RegisterOnInitializeHandler), ActionWrapper(SingleParamHandler(RegisterOnInitializeHandler))},
                     {ActionToString(KeyActions::RegisterOnConfigurationChangeHandler), ActionWrapper(InitializeHandler(RegisterOnConfigurationChangeHandler))},
                     {ActionToString(KeyActions::RegisterOnKeyDownHandler), ActionWrapper(SingleParamHandler(RegisterControlSystemMediaPlayerHandler))},
                     {ActionToString(SystemActions::UseSystemControlSystemMediaPlayer), ActionWrapper(NotificationHandler(Notify))},
                     {ActionToString(KeyActions::RegisterOnDeactivateHandler), ActionWrapper(DeactivateHandler(RegisterOnDeactivateHandler))}});

  this->RegisterKey("System API - open application",
                    {{ActionToString(KeyActions::RegisterOnInitializeHandler), ActionWrapper(SingleParamHandler(RegisterOnInitializeHandler))},
                     {ActionToString(KeyActions::RegisterOnConfigurationChangeHandler), ActionWrapper(InitializeHandler(RegisterOnConfigurationChangeHandler))},
                     {ActionToString(KeyActions::RegisterOnKeyDownHandler), ActionWrapper(SingleParamHandler(RegisterOpenChromeAppHandler))},
                     {ActionToString(SystemActions::UseOpenApp), ActionWrapper(NotificationHandler(Notify))},
                     {ActionToString(KeyActions::RegisterOnDeactivateHandler), ActionWrapper(DeactivateHandler(RegisterOnDeactivateHandler))}});

  this->RegisterKey("System API - keystrokes",
                    {{ActionToString(KeyActions::RegisterOnInitializeHandler), ActionWrapper(SingleParamHandler(RegisterOnInitializeHandler))},
                     {ActionToString(KeyActions::RegisterOnConfigurationChangeHandler), ActionWrapper(InitializeHandler(RegisterOnConfigurationChangeHandler))},
                     {ActionToString(KeyActions::RegisterOnKeyDownHandler), ActionWrapper(SingleParamHandler(RegisterOpenChromeAppHandler))},
                     {ActionToString(SystemActions::UseKeystrokes), ActionWrapper(NotificationHandler(Notify))},
                     {ActionToString(KeyActions::RegisterOnDeactivateHandler), ActionWrapper(DeactivateHandler(RegisterOnDeactivateHandler))}});

  // Register Key
  this->RegisterKey("Widget nr 2 Key",
                    {{ActionToString(KeyActions::RegisterOnInitializeHandler), ActionWrapper(SingleParamHandler(RegisterOnInitializeHandler))},
                     {ActionToString(KeyActions::RegisterOnKeyDownHandler), ActionWrapper(SingleParamHandler(RegisterOnKeyDownHandler))},
                     {ActionToString(KeyActions::RegisterOnKeyUpHandler), ActionWrapper(SingleParamHandler(RegisterOnKeyUpHandler))},
                     {ActionToString(KeyActions::RegisterOnConfigurationChangeHandler), ActionWrapper(InitializeHandler(RegisterOnConfigurationChangeHandler))},
                     {ActionToString(SystemActions::UseSystemMuteMicrophone), ActionWrapper(NotificationHandler(Notify))},
                     {ActionToString(SystemActions::UseSystemUnmuteMicrophone), ActionWrapper(NotificationHandler(Notify))},
                     {ActionToString(SystemActions::UseSystemTakeScreenshot), ActionWrapper(NotificationHandler(Notify))},
                     {ActionToString(SystemActions::UseOpenApp), ActionWrapper(NotificationHandler(Notify))},
                     {ActionToString(SystemActions::UseKeystrokes), ActionWrapper(NotificationHandler(Notify))},
                     {ActionToString(SystemActions::UseSystemControlSystemMediaPlayer), ActionWrapper(NotificationHandler(Notify))},
                     {ActionToString(KeyActions::RegisterOnDeactivateHandler), ActionWrapper(DeactivateHandler(RegisterOnDeactivateHandler))}});

  // Register Knob
  this->RegisterKnob("Widget nr 3 Knob",
                     {{ActionToString(KnobActions::RegisterOnInitializeHandler), ActionWrapper(SingleParamHandler(RegisterOnInitializeHandler))},
                      {ActionToString(KnobActions::RegisterOnChangeHandler), ActionWrapper(ChangeHandler(RegisterVolumeOnChangeHandler))},
                      {ActionToString(SystemActions::UseMicrophoneSystemVolume), ActionWrapper(ChangeHandler(UseMicrophoneSystemVolumeHandler))},
                      {ActionToString(KnobActions::RegisterOnDeactivateHandler), ActionWrapper(DeactivateHandler(RegisterOnDeactivateHandler))}});

  // Register Slider
  this->RegisterSlider("Widget nr 5 Slider",
                       {{ActionToString(SliderActions::RegisterOnChangeHandler), ActionWrapper(ChangeHandler(RegisterVolumeOnChangeHandler))},
                        {ActionToString(SystemActions::UseSystemVolume), ActionWrapper(ChangeHandler(UseSystemVolumeHandler))}});
}

void Plugin::RegisterLedCluster(const std::string &name, const std::vector<std::pair<std::string, ActionWrapper>> &actions)
{
  Widget ledCluster(name, "LedCluster");

  for (const auto &actionPair : actions)
  {
    ledCluster.RegisterAction(actionPair.first, actionPair.second);
  }

  widgets[name] = std::move(ledCluster);
}

void Plugin::RegisterKey(const std::string &name, const std::vector<std::pair<std::string, ActionWrapper>> &actions)
{
  Widget key(name, "Key");

  for (const auto &actionPair : actions)
  {
    key.RegisterAction(actionPair.first, actionPair.second);
  }

  widgets[name] = std::move(key);
}

void Plugin::RegisterKnob(const std::string &name, const std::vector<std::pair<std::string, ActionWrapper>> &actions)
{
  Widget knob(name, "Knob");

  for (const auto &actionPair : actions)
  {
    knob.RegisterAction(actionPair.first, actionPair.second);
  }

  widgets[name] = std::move(knob);
}

void Plugin::RegisterSwitch(const std::string &name, const std::vector<std::pair<std::string, ActionWrapper>> &actions)
{
  Widget sw(name, "Switch");

  for (const auto &actionPair : actions)
  {
    sw.RegisterAction(actionPair.first, actionPair.second);
  }

  widgets[name] = std::move(sw);
}

void Plugin::RegisterSlider(const std::string &name, const std::vector<std::pair<std::string, ActionWrapper>> &actions)
{
  Widget slider(name, "Slider");

  for (const auto &actionPair : actions)
  {
    slider.RegisterAction(actionPair.first, actionPair.second);
  }

  widgets[name] = std::move(slider);
}
