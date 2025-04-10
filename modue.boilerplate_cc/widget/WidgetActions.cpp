#include "WidgetActions.h"

std::string ActionToString(BaseActions action)
{
  switch (action)
  {
  case BaseActions::RegisterOnInitializeHandler:
    return "registerOnInitializeHandler";
  case BaseActions::RegisterOnDeactivateHandler:
    return "registerOnDeactivateHandler";
  case BaseActions::RegisterOnConfigurationChangeHandler:
    return "registerOnConfigurationChangeHandler";
  }
  return "";
}

std::string ActionToString(SystemActions action)
{
  switch (action)
  {
  case SystemActions::UseSystemMuteMicrophone:
    return "useSystemMuteMicrophone";
  case SystemActions::UseSystemUnmuteMicrophone:
    return "useSystemUnmuteMicrophone";
  case SystemActions::UseSystemInstalledApps:
    return "useSystemInstalledApps";
  case SystemActions::UseAudioApps:
    return "useAudioApps";
  case SystemActions::UseSystemAvailableMicrophoneDevices:
    return "useSystemAvailableMicrophoneDevices";
  case SystemActions::UseSystemVolume:
    return "useSystemVolume";
  case SystemActions::UseMicrophoneSystemVolume:
    return "useMicrophoneSystemVolume";
  case SystemActions::UseSystemMonitorResources:
    return "useSystemMonitorResources";
  case SystemActions::UseSystemTakeScreenshot:
    return "useSystemTakeScreenshot";
  case SystemActions::UseSystemControlSystemMediaPlayer:
    return "useSystemControlSystemMediaPlayer";
  case SystemActions::UseOpenApp:
    return "useOpenApp";
  case SystemActions::UseKeystrokes:
    return "useKeystrokes";
  case SystemActions::UseSystemAvailableDevices:
    return "useSystemAvailableDevices";
  }
  return "";
}

std::string ActionToString(SliderActions action)
{
  switch (action)
  {
  case SliderActions::RegisterOnChangeHandler:
    return "registerOnChangeHandler";
  default:
    return ActionToString(static_cast<BaseActions>(action));
  }
}

std::string ActionToString(KeyActions action)
{
  switch (action)
  {
  case KeyActions::RegisterOnKeyDownHandler:
    return "registerOnKeyDownHandler";
  case KeyActions::RegisterOnKeyUpHandler:
    return "registerOnKeyUpHandler";
  default:
    return ActionToString(static_cast<BaseActions>(action));
  }
}

std::string ActionToString(KnobActions action)
{
  switch (action)
  {
  case KnobActions::RegisterOnChangeHandler:
    return "registerOnChangeHandler";
  default:
    return ActionToString(static_cast<BaseActions>(action));
  }
}

std::string ActionToString(SwitchActions action)
{
  switch (action)
  {
  case SwitchActions::RegisterOnChangeHandler:
    return "registerOnChangeHandler";
  default:
    return ActionToString(static_cast<BaseActions>(action));
  }
}

std::string ActionToString(LedClusterActions action)
{
  return ActionToString(static_cast<BaseActions>(action));
}

std::string ActionToString(ConfigurationActions action)
{
  switch (action)
  {
  case ConfigurationActions::AddInput:
    return "addInput";
  case ConfigurationActions::AddDropdown:
    return "addDropdown";
  case ConfigurationActions::AddButton:
    return "addButton";
  case ConfigurationActions::UseInternalAuthorizationHandler:
    return "useInternalAuthorizationHandler";
  default:
    return "Unknown Configuration Action";
  }
}
