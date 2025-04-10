#include "RegisterHandlers.h"
#include "./../actions/BaseEvents/Set.h"
#include "./../actions/BaseEvents/SetArray.h"
#include "./../actions/SystemEvents/SetSystemVolume.h"
#include "./../actions/SystemEvents/MuteMicrophone.h"
#include "./../actions/SystemEvents/UnmuteMicrophone.h"
#include "./../actions/SystemEvents/TakeScreenshot.h"
#include "./../utils/FileLogger.h"
#include <chrono>
#include <random>
#include <vector>
#include <napi.h>
#include <string>
#include <iostream>

std::string RegisterOnInitializeHandlerLed(Napi::Value instance)
{
  if (!instance.IsObject())
  {
    return "Invalid instance provided";
  }

  Napi::Object instanceObj = instance.As<Napi::Object>();
  if (!instanceObj.Has("set") || !instanceObj.Get("set").IsFunction())
  {
    return "Instance does not have a callable set function";
  }

  Napi::Value ledValue = instanceObj.Get("numberOfLeds");
  if (!ledValue)
  {
    return "Instance does not have a valid 'numberOfLeds' property 1";
  }
  if (!ledValue.IsNumber())
  {
    return "Instance does not have a valid 'numberOfLeds' property 2";
  }

  int numberOfLeds = ledValue.As<Napi::Number>().Int32Value();

  auto setFunction = instanceObj.Get("set").As<Napi::Function>();
  std::string actionName = "registerOnInitializeHandler";

  const std::vector<std::string> colorOptions = {
      "#31e000FF", // Green
      "#e0d100FF", // Yellow
      "#FF0000FF"  // Red
  };

  std::vector<std::string> ledsToFlash(numberOfLeds);

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, colorOptions.size() - 1);

  for (int index = 0; index < numberOfLeds; ++index)
  {
    ledsToFlash[index] = colorOptions[dis(gen)];
  }

  // Call SetArray with the generated LED array
  SetArray(instance.Env(), setFunction, instanceObj, actionName, ledsToFlash);

  return "LedCluster initialized and LED colors set randomly";
}

std::string RegisterOnInitializeHandler(Napi::Value instance)
{
  return "registerOnInitializeHandler initialized ";
}

std::string RegisterOnConfigurationChangeHandler(Napi::Value instance, Napi::Value configuration)
{
  if (!configuration.IsObject())
  {
    return "Invalid configuration provided. Expected an object.";
  }

  Napi::Object configObj = configuration.As<Napi::Object>();

  if (!configObj.Has("key") || !configObj.Get("key").IsString())
  {
    return "Configuration object does not have a valid 'key' property.";
  }

  if (!configObj.Has("value"))
  {
    return "Configuration object does not have a 'value' property.";
  }

  std::string key = configObj.Get("key").As<Napi::String>();
  Napi::Value value = configObj.Get("value");

  std::string valueStr;
  if (value.IsString())
  {
    valueStr = value.As<Napi::String>();
  }
  else if (value.IsNumber())
  {
    valueStr = std::to_string(value.As<Napi::Number>().DoubleValue());
  }
  else if (value.IsBoolean())
  {
    valueStr = value.As<Napi::Boolean>() ? "true" : "false";
  }
  else
  {
    valueStr = "Unsupported value type";
  }

  std::string result = "Configuration changed - Key: " + key + ", Value: " + valueStr;
  return result;
}

std::string RegisterAppsOrDeviceList(Napi::Value instance, Napi::Value collection)
{
  if (collection.IsObject())
  {
    Napi::Object collectionObject = collection.As<Napi::Object>();

    Napi::String jsonString = collectionObject.ToString();

    return jsonString.Utf8Value();
  }
  else if (collection.IsArray())
  {
    Napi::Array collectionArray = collection.As<Napi::Array>();

    Napi::String jsonString = collectionArray.ToString();

    return jsonString.Utf8Value();
  }
  else
  {
    return "Collection is not a valid object or array to serialize.";
  }

  return "Unhandled collection type.";
}

std::string RegisterResourceHandler(Napi::Value instance, Napi::Value resources)
{
  if (!resources.IsObject())
  {
    return "Error: resources is not an object";
  }

  Napi::Object resourcesObj = resources.As<Napi::Object>();

  if (!resourcesObj.Has("cpu"))
  {
    return "Error: resources does not have property 'cpu'";
  }

  Napi::Value cpuValue = resourcesObj.Get("cpu");
  if (!cpuValue.IsObject())
  {
    return "Error: cpu is not an object";
  }

  Napi::Object cpuObj = cpuValue.As<Napi::Object>();

  if (!cpuObj.Has("usageInPercentage"))
  {
    return "Error: cpu does not have property 'usageInPercentage'";
  }

  Napi::Value usageValue = cpuObj.Get("usageInPercentage");

  if (!usageValue.IsNumber())
  {
    return "Error: usageInPercentage is not a number";
  }

  if (!instance.IsObject())
  {
    return "Invalid instance provided";
  }

  Napi::Object instanceObj = instance.As<Napi::Object>();
  if (!instanceObj.Has("set") || !instanceObj.Get("set").IsFunction())
  {
    return "Instance does not have a callable set function";
  }

  Napi::Value ledValue = instanceObj.Get("numberOfLeds");
  if (!ledValue)
  {
    return "Instance does not have a valid 'numberOfLeds' property 1";
  }
  if (!ledValue.IsNumber())
  {
    return "Instance does not have a valid 'numberOfLeds' property 2";
  }

  int numberOfLeds = ledValue.As<Napi::Number>().Int32Value();

  double usage = usageValue.As<Napi::Number>().DoubleValue();

  auto setFunction = instanceObj.Get("set").As<Napi::Function>();
  std::string actionName = "registerOnInitializeHandler";

  int ledsToTurnOn = static_cast<int>(std::round((usage / 100.0) * numberOfLeds));

  const std::vector<std::string> colorOptions = {
      "#31e000FF",
      "#e0d100FF",
      "#FF0000FF"};

  std::vector<std::string> ledsToFlash(numberOfLeds);

  std::string color;
  if (usage <= 50.0)
  {
    color = colorOptions[0];
  }
  else if (usage <= 75.0)
  {
    color = colorOptions[1];
  }
  else
  {
    color = colorOptions[2];
  }

  for (int index = 0; index < numberOfLeds; ++index)
  {
    if (index < ledsToTurnOn)
    {
      ledsToFlash[index] = color;
    }
    else
    {
      ledsToFlash[index] = "#00000000";
    }
  }

  SetArray(instance.Env(), setFunction, instanceObj, actionName, ledsToFlash);

  std::string result = "RegisterOnConfigurationChangeHandler fired. CPU usage: " + std::to_string(usage) + "%";

  return result;
}

std::string RegisterOnKeyDownHandler(Napi::Value instance)
{
  return "Key down event handled";
}

std::string RegisterOnKeyDownAppsListHandler(Napi::Value instance)
{
  if (!instance.IsObject())
  {
    return "Invalid instance: not an object.";
  }

  Napi::Object obj = instance.As<Napi::Object>();

  if (!obj.HasOwnProperty("applications"))
  {
    return "No applications array found at root.";
  }

  Napi::Value appsValue = obj.Get("applications");
  if (!appsValue.IsArray())
  {
    return "Applications field is not an array.";
  }

  Napi::Array applications = appsValue.As<Napi::Array>();

  std::string appsList = "Applications: ";

  uint32_t length = applications.Length();
  for (uint32_t i = 0; i < length; ++i)
  {
    Napi::Value appValue = applications.Get(i);
    if (appValue.IsObject())
    {
      Napi::Object appObject = appValue.As<Napi::Object>();
      if (appObject.HasOwnProperty("name"))
      {
        std::string appName = appObject.Get("name").As<Napi::String>().Utf8Value();
        appsList += appName + ", ";
      }
    }
  }

  if (appsList.size() > 2)
  {
    appsList.erase(appsList.size() - 2, 2);
  }

  return appsList;
}

std::string RegisterOnKeyDownAudioAppsListHandler(Napi::Value instance)
{
  if (!instance.IsObject())
  {
    return "Invalid instance: not an object.";
  }

  Napi::Object obj = instance.As<Napi::Object>();

  if (!obj.HasOwnProperty("availableAudioApplications"))
  {
    return "No availableAudioApplications array found at root.";
  }

  Napi::Value appsValue = obj.Get("availableAudioApplications");
  if (!appsValue.IsArray())
  {
    return "availableAudioApplications field is not an array.";
  }

  Napi::Array applications = appsValue.As<Napi::Array>();

  std::string appsList = "availableAudioApplications: ";

  uint32_t length = applications.Length();
  for (uint32_t i = 0; i < length; ++i)
  {
    Napi::Value appValue = applications.Get(i);
    if (appValue.IsObject())
    {
      Napi::Object appObject = appValue.As<Napi::Object>();
      if (appObject.HasOwnProperty("name"))
      {
        std::string appName = appObject.Get("name").As<Napi::String>().Utf8Value();
        appsList += appName + ", ";
      }
    }
  }

  if (appsList.size() > 2)
  {
    appsList.erase(appsList.size() - 2, 2);
  }

  return appsList;
}

std::string RegisterOnKeyDownSpeakersListHandler(Napi::Value instance)
{
  if (!instance.IsObject())
  {
    return "Invalid instance: not an object.";
  }

  Napi::Object obj = instance.As<Napi::Object>();

  if (!obj.HasOwnProperty("speakers"))
  {
    return "No speakers array found at root.";
  }

  Napi::Value appsValue = obj.Get("speakers");
  if (!appsValue.IsArray())
  {
    return "speakers field is not an array.";
  }

  Napi::Array applications = appsValue.As<Napi::Array>();

  std::string appsList = "speakers: ";

  uint32_t length = applications.Length();
  for (uint32_t i = 0; i < length; ++i)
  {
    Napi::Value appValue = applications.Get(i);
    if (appValue.IsObject())
    {
      Napi::Object appObject = appValue.As<Napi::Object>();
      if (appObject.HasOwnProperty("name"))
      {
        std::string appName = appObject.Get("name").As<Napi::String>().Utf8Value();
        appsList += appName + ", ";
      }
    }
  }

  if (appsList.size() > 2)
  {
    appsList.erase(appsList.size() - 2, 2);
  }

  return appsList;
}

std::string RegisterOnKeyDownMicrophonesListHandler(Napi::Value instance)
{
  if (!instance.IsObject())
  {
    return "Invalid instance: not an object.";
  }

  Napi::Object obj = instance.As<Napi::Object>();

  if (!obj.HasOwnProperty("microphones"))
  {
    return "No microphones array found at root.";
  }

  Napi::Value appsValue = obj.Get("microphones");
  if (!appsValue.IsArray())
  {
    return "microphones field is not an array.";
  }

  Napi::Array applications = appsValue.As<Napi::Array>();

  std::string appsList = "microphones: ";

  uint32_t length = applications.Length();
  for (uint32_t i = 0; i < length; ++i)
  {
    Napi::Value appValue = applications.Get(i);
    if (appValue.IsObject())
    {
      Napi::Object appObject = appValue.As<Napi::Object>();
      if (appObject.HasOwnProperty("name"))
      {
        std::string appName = appObject.Get("name").As<Napi::String>().Utf8Value();
        appsList += appName + ", ";
      }
    }
  }

  if (appsList.size() > 2)
  {
    appsList.erase(appsList.size() - 2, 2);
  }

  return appsList;
}

std::string RegisterMuteUnmuteOnKeyDownHandler(Napi::Value instance)
{
  if (!instance.IsObject())
  {
    return "Invalid instance provided";
  }

  Napi::Object instanceObj = instance.As<Napi::Object>();
  if ((!instanceObj.Has("muteMicrophone") || !instanceObj.Get("muteMicrophone").IsFunction()) ||
      (!instanceObj.Has("unmuteMicrophone") || !instanceObj.Get("unmuteMicrophone").IsFunction()))
  {
    return "Instance does not have callable mute or unmute function";
  }

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 1);
  bool shouldMute = dis(gen) == 0;

  if (shouldMute)
  {
    auto muteFunction = instanceObj.Get("muteMicrophone").As<Napi::Function>();
    std::string actionName = "muteMicrophone";
    MuteMicrophone(instance.Env(), muteFunction, instanceObj, actionName);
    return "MuteMicrophone called";
  }
  else
  {
    auto unmuteFunction = instanceObj.Get("unmuteMicrophone").As<Napi::Function>();
    std::string actionName = "unmuteMicrophone";
    UnmuteMicrophone(instance.Env(), unmuteFunction, instanceObj, actionName);
    return "UnmuteMicrophone called";
  }
}

std::string RegisterTakeScreenshotHandler(Napi::Value instance)
{
  if (!instance.IsObject())
  {
    return "Invalid instance provided";
  }

  Napi::Object instanceObj = instance.As<Napi::Object>();
  if (!instanceObj.Has("takeScreenshot") || !instanceObj.Get("takeScreenshot").IsFunction())
  {
    return "Instance does not have callable takeScreenshot function";
  }

  auto screenshotFunction = instanceObj.Get("takeScreenshot").As<Napi::Function>();

  int randomNumber = std::rand() % 1000 + 1;
  std::string fileName = "screenshot" + std::to_string(randomNumber) + ".jpg";

  std::string actionName = "takeScreenshot";
  TakeScreenshot(instance.Env(), screenshotFunction, instanceObj, fileName, actionName);

  return "TakeScreenshot called with filename: " + fileName;
}

std::string RegisterControlSystemMediaPlayerHandler(Napi::Value instance)
{
  if (!instance.IsObject())
  {
    return "Invalid instance provided";
  }

  Napi::Object instanceObj = instance.As<Napi::Object>();
  if (!instanceObj.Has("setControlSystemMediaPlayer") || !instanceObj.Get("setControlSystemMediaPlayer").IsFunction())
  {
    return "Instance does not have callable setControlSystemMediaPlayer function";
  }

  auto setControlFunction = instanceObj.Get("setControlSystemMediaPlayer").As<Napi::Function>();

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1, 3);
  int randomChoice = dis(gen);

  std::string actionName;

  switch (randomChoice)
  {
  case 1:
    actionName = "play/pause";
    setControlFunction.Call(instanceObj, {Napi::String::New(instance.Env(), actionName)});
    logToFile("Instance has play/pause MediaPlayer");
    break;
  case 2:
    actionName = "previous";
    setControlFunction.Call(instanceObj, {Napi::String::New(instance.Env(), actionName)});
    logToFile("Instance has send previous to MediaPlayer");
    break;
  case 3:
    actionName = "next";
    setControlFunction.Call(instanceObj, {Napi::String::New(instance.Env(), actionName)});
    logToFile("Instance has send next to MediaPlayer");
    break;
  default:
    return "Unexpected error in generating random choice";
  }

  return "setControlSystemMediaPlayer called with action: " + actionName;
}

std::string RegisterOpenChromeAppHandler(Napi::Value instance)
{
  if (!instance.IsObject())
  {
    return "Invalid instance provided";
  }

  Napi::Object instanceObj = instance.As<Napi::Object>();
  if (!instanceObj.Has("openApp") || !instanceObj.Get("openApp").IsFunction())
  {
    return "Instance does not have a callable openApp function";
  }

  auto openAppFunction = instanceObj.Get("openApp").As<Napi::Function>();

  std::string appName = "Chrome";

  openAppFunction.Call(instanceObj, {Napi::String::New(instance.Env(), appName)});
  logToFile("Called openApp with argument: " + appName);

  return "openApp called with application name: " + appName;
}

std::string RegisterPressKeystrokesHandler(Napi::Value instance)
{
  if (!instance.IsObject())
  {
    return "Invalid instance provided";
  }

  Napi::Object instanceObj = instance.As<Napi::Object>();
  if (!instanceObj.Has("pressKeystrokes") || !instanceObj.Get("pressKeystrokes").IsFunction())
  {
    return "Instance does not have a callable pressKeystrokes function";
  }

  if (!instanceObj.Has("configuration") || !instanceObj.Get("configuration").IsObject())
  {
    return "Instance does not have a valid configuration object";
  }

  Napi::Object configObj = instanceObj.Get("configuration").As<Napi::Object>();

  std::vector<std::pair<std::string, int>> keystrokes = {
      {"MetaLeft", 55},
      {"KeyT", 17}};

  std::vector<Napi::Number> keyCodes;
  for (const auto &keystroke : keystrokes)
  {
    keyCodes.push_back(Napi::Number::New(instance.Env(), keystroke.second));
  }

  std::string applicationName = "Chrome"; // Default
  if (configObj.Has("selectedSystem") && configObj.Get("selectedSystem").IsNumber())
  {
    int selectedSystem = configObj.Get("selectedSystem").As<Napi::Number>().Int32Value();
    applicationName = (selectedSystem == 2) ? "com.google.Chrome" : "Chrome";
  }

  auto pressKeystrokesFunction = instanceObj.Get("pressKeystrokes").As<Napi::Function>();

  Napi::Array keyCodesArray = Napi::Array::New(instance.Env(), keyCodes.size());
  for (size_t i = 0; i < keyCodes.size(); i++)
  {
    keyCodesArray[i] = keyCodes[i];
  }

  pressKeystrokesFunction.Call(instanceObj, {keyCodesArray, Napi::String::New(instance.Env(), applicationName)});
  logToFile("Called pressKeystrokes with keyCodes: " + std::to_string(keyCodes.size()) + ", applicationName: " + applicationName);

  return "pressKeystrokes called with application: " + applicationName;
}

std::string RegisterOnKeyUpHandler(Napi::Value instance)
{
  return "Key up event handled";
}

std::string RegisterOnDeactivateHandler(Napi::String id)
{
  std::string idStr = id.Utf8Value();

  return "Deactivated successfully: " + idStr;
}

std::string RegisterOnChangeHandler(Napi::Value instance, Napi::Number value)
{
  double numericValue = value.DoubleValue(); // Convert Napi::Number to double
  logToFile("RegisterOnChangeHandler called with value: " + std::to_string(numericValue));

  return "RegisterOnChangeHandler w c++:  " + std::to_string(numericValue);
}

std::string RegisterSwitchOnChangeHandler(Napi::Value instance, Napi::Value value)
{
  bool boolValue = value.ToBoolean().Value();
  logToFile("RegisterOnChangeHandler called with value: " + std::string(boolValue ? "true" : "false"));

  return "RegisterOnChangeHandler in C++: " + std::string(boolValue ? "true" : "false");
}

std::string RegisterVolumeOnChangeHandler(Napi::Value instance, Napi::Number value)
{
  if (!instance.IsObject())
  {
    return "Invalid instance provided";
  }

  Napi::Object instanceObj = instance.As<Napi::Object>();
  if (!instanceObj.Has("setSystemVolume") || !instanceObj.Get("setSystemVolume").IsFunction())
  {
    return "Instance does not have a callable setSystemVolume function";
  }

  auto setFunction = instanceObj.Get("setSystemVolume").As<Napi::Function>();
  std::string actionName = "RegisterOnChangeHandler";

  double numericValue = value.DoubleValue(); // Convert Napi::Number to double
  logToFile("RegisterOnChangeHandler called with value: " + std::to_string(numericValue));

  SetSystemVolume(instance.Env(), setFunction, instanceObj, value);

  return "RegisterOnChangeHandler w c++:  " + std::to_string(numericValue);
}

std::string RegisterMicrophoneVolumeOnChangeHandler(Napi::Value instance, Napi::Number value)
{
  if (!instance.IsObject())
  {
    return "Invalid instance provided";
  }

  Napi::Object instanceObj = instance.As<Napi::Object>();
  if (!instanceObj.Has("setSystemVolume") || !instanceObj.Get("setSystemVolume").IsFunction())
  {
    return "Instance does not have a callable setSystemVolume function";
  }

  auto setFunction = instanceObj.Get("setSystemVolume").As<Napi::Function>();
  std::string actionName = "RegisterOnChangeHandler";

  double numericValue = value.DoubleValue(); // Convert Napi::Number to double
  logToFile("RegisterOnChangeHandler called with value: " + std::to_string(numericValue));

  SetSystemVolume(instance.Env(), setFunction, instanceObj, value, "Mike");

  return "RegisterOnChangeHandler w c++:  " + std::to_string(numericValue);
}

std::string UseSystemVolumeHandler(Napi::Value instance, Napi::Number value)
{
  if (!instance.IsObject())
  {
    return "Invalid instance provided";
  }

  Napi::Object instanceObj = instance.As<Napi::Object>();
  if (!instanceObj.Has("set") || !instanceObj.Get("set").IsFunction())
  {
    return "Instance does not have a callable set function";
  }

  auto setFunction = instanceObj.Get("set").As<Napi::Function>();
  std::string actionName = "useSystemVolume";

  double numericValue = value.DoubleValue(); // Convert Napi::Number to double
  Set(instance.Env(), setFunction, instanceObj, numericValue, actionName);

  return "UseSystemVolumeHandler w c++: " + std::to_string(numericValue);
}

std::string UseMicrophoneSystemVolumeHandler(Napi::Value instance, Napi::Number value)
{
  if (!instance.IsObject())
  {
    return "Invalid instance provided";
  }

  Napi::Object instanceObj = instance.As<Napi::Object>();
  if (!instanceObj.Has("set") || !instanceObj.Get("set").IsFunction())
  {
    return "Instance does not have a callable set function";
  }

  auto setFunction = instanceObj.Get("set").As<Napi::Function>();
  std::string actionName = "useMicrophoneSystemVolume";

  double numericValue = value.DoubleValue(); // Convert Napi::Number to double
  Set(instance.Env(), setFunction, instanceObj, numericValue, actionName);

  return "useMicrophoneSystemVolume w c++: " + std::to_string(numericValue);
}

std::string Notify()
{
  return "Module initialized";
}
