#ifndef WIDGET_ACTIONS_H
#define WIDGET_ACTIONS_H

#include <string>

enum class BaseActions
{
  RegisterOnInitializeHandler,
  RegisterOnDeactivateHandler,
  RegisterOnConfigurationChangeHandler
};

enum class SliderActions : int
{
  RegisterOnInitializeHandler = static_cast<int>(BaseActions::RegisterOnInitializeHandler),
  RegisterOnDeactivateHandler = static_cast<int>(BaseActions::RegisterOnDeactivateHandler),
  RegisterOnConfigurationChangeHandler = static_cast<int>(BaseActions::RegisterOnConfigurationChangeHandler),
  RegisterOnChangeHandler
};

enum class KeyActions : int
{
  RegisterOnInitializeHandler = static_cast<int>(BaseActions::RegisterOnInitializeHandler),
  RegisterOnDeactivateHandler = static_cast<int>(BaseActions::RegisterOnDeactivateHandler),
  RegisterOnConfigurationChangeHandler = static_cast<int>(BaseActions::RegisterOnConfigurationChangeHandler),
  RegisterOnKeyDownHandler,
  RegisterOnKeyUpHandler
};

enum class KnobActions : int
{
  RegisterOnInitializeHandler = static_cast<int>(BaseActions::RegisterOnInitializeHandler),
  RegisterOnDeactivateHandler = static_cast<int>(BaseActions::RegisterOnDeactivateHandler),
  RegisterOnConfigurationChangeHandler = static_cast<int>(BaseActions::RegisterOnConfigurationChangeHandler),
  RegisterOnChangeHandler
};

enum class SwitchActions : int
{
  RegisterOnInitializeHandler = static_cast<int>(BaseActions::RegisterOnInitializeHandler),
  RegisterOnDeactivateHandler = static_cast<int>(BaseActions::RegisterOnDeactivateHandler),
  RegisterOnConfigurationChangeHandler = static_cast<int>(BaseActions::RegisterOnConfigurationChangeHandler),
  RegisterOnChangeHandler
};

enum class LedClusterActions : int
{
  RegisterOnInitializeHandler = static_cast<int>(BaseActions::RegisterOnInitializeHandler),
  RegisterOnDeactivateHandler = static_cast<int>(BaseActions::RegisterOnDeactivateHandler),
  RegisterOnConfigurationChangeHandler = static_cast<int>(BaseActions::RegisterOnConfigurationChangeHandler)
};

enum class SystemActions : int
{
  UseSystemMuteMicrophone,
  UseSystemUnmuteMicrophone,
  UseSystemInstalledApps,
  UseAudioApps,
  UseSystemAvailableMicrophoneDevices,
  UseSystemVolume,
  UseMicrophoneSystemVolume,
  UseSystemAvailableDevices,
  UseSystemMonitorResources,
  UseSystemTakeScreenshot,
  UseSystemControlSystemMediaPlayer,
  UseOpenApp,
  UseKeystrokes
};

enum class ConfigurationActions : int
{
  AddInput,
  AddDropdown,
  AddButton,
  UseInternalAuthorizationHandler
};

std::string ActionToString(BaseActions action);
std::string ActionToString(SliderActions action);
std::string ActionToString(KeyActions action);
std::string ActionToString(KnobActions action);
std::string ActionToString(SwitchActions action);
std::string ActionToString(LedClusterActions action);
std::string ActionToString(SystemActions action);
std::string ActionToString(ConfigurationActions action);

#endif
