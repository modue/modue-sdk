#include "Plugin.h"
#include "./../utils/FileLogger.h"
#include "./../widget/WidgetActions.h"

Napi::Value Plugin::InvokeAction(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();

  if (info.Length() < 2 || !info[0].IsString() || !info[1].IsString())
  {
    std::string errorMessage = "Expected widget ID and action name as arguments";
    logToFile("InvokeAction Error: " + errorMessage);
    Napi::TypeError::New(env, errorMessage).ThrowAsJavaScriptException();
    return env.Null();
  }

  std::string widgetId = info[0].As<Napi::String>();
  std::string actionName = info[1].As<Napi::String>();
  logToFile("InvokeAction called with widgetId: " + widgetId + ", actionName: " + actionName);

  if (actionName == ActionToString(ConfigurationActions::AddInput))
  {
    Napi::Array inputConfigurations = Napi::Array::New(env);
    int index = 0;

    auto widgetIt = widgets.find(widgetId);
    if (widgetIt != widgets.end())
    {
      Widget &widget = widgetIt->second;
      auto actions = widget.GetActions(actionName);

      for (const auto &action : actions)
      {
        const ConfigurationMetadata &configMetadata = action.GetConfigurationMetadata();

        Napi::Object inputConfig = Napi::Object::New(env);
        inputConfig.Set("key", configMetadata.key);
        inputConfig.Set("name", configMetadata.name);
        inputConfig.Set("description", configMetadata.description);
        inputConfig.Set("type", configMetadata.type);

        inputConfigurations.Set(index++, inputConfig);
      }
    }

    logToFile("InvokeAction returning inputConfigurations with size: " + std::to_string(index));
    return inputConfigurations;
  }

  if (actionName == "registerOnChangeHandler" || actionName == "useSystemVolume" || actionName == "useMicrophoneSystemVolume")
  {
    if (info.Length() < 4 || !info[2].IsObject() || !info[3].IsNumber())
    {
      if (info.Length() < 4 || !info[2].IsObject() || !info[3].IsBoolean())
      {
        std::string errorMessage = "Expected instance and value as arguments for " + actionName;
        logToFile("InvokeAction Error: " + errorMessage);
        Napi::TypeError::New(env, errorMessage).ThrowAsJavaScriptException();
        return env.Null();
      }

      Napi::Value instance = info[2];
      Napi::Value value = info[3];

      bool boolValue = value.As<Napi::Boolean>().Value();
      logToFile("InvokeAction proceeding with instance and boolean value: " + std::string(boolValue ? "true" : "false"));

      std::string result = widgets[widgetId].InvokeAction(actionName, instance, value);
      logToFile("InvokeAction result: " + result);
      return Napi::String::New(env, result);
    }
    Napi::Value instance = info[2];
    Napi::Number value = info[3].As<Napi::Number>();
    logToFile("InvokeAction proceeding with instance and value: " + std::to_string(value.DoubleValue()));
    std::string result = widgets[widgetId].InvokeAction(actionName, instance, value);
    logToFile("InvokeAction result: " + result);
    return Napi::String::New(env, result);
  }
  else if (actionName == "registerOnDeactivateHandler")
  {
    if (info.Length() < 3 || !info[2].IsString())
    {
      std::string errorMessage = "Expected string as arguments for " + actionName;
      logToFile("InvokeAction Error: " + errorMessage);
      Napi::TypeError::New(env, errorMessage).ThrowAsJavaScriptException();
      return env.Null();
    }
    Napi::String id = info[2].As<Napi::String>();
    logToFile("InvokeAction proceeding with id: " + id.Utf8Value());
    std::string result = widgets[widgetId].InvokeAction(actionName, id);
    logToFile("InvokeAction result: " + result);
    return Napi::String::New(env, result);
  }
  else if (actionName == "registerOnInitializeHandler" || actionName == "registerOnKeyDownHandler" || actionName == "registerOnKeyUpHandler")
  {
    if (info.Length() < 3 || !info[2].IsObject())
    {
      std::string errorMessage = "Expected string as arguments for " + actionName;
      logToFile("InvokeAction Error: " + errorMessage);
      Napi::TypeError::New(env, errorMessage).ThrowAsJavaScriptException();
      return env.Null();
    }
    Napi::Value instance = info[2];
    logToFile("InvokeAction proceeding ");
    std::string result = widgets[widgetId].InvokeAction(actionName, instance);
    logToFile("InvokeAction result: " + result);
    return Napi::String::New(env, result);
  }
  else if (actionName == "useSystemMonitorResources" || actionName == "useSystemInstalledApps" || actionName == "useAudioApps" || actionName == "useSystemAvailableMicrophoneDevices" || actionName == "useSystemAvailableDevices" || actionName == "registerOnConfigurationChangeHandler")
  {
    if (info.Length() < 4 || !info[2].IsObject() || !info[3].IsObject())
    {
      std::string errorMessage = "Expected string as arguments for " + actionName;
      logToFile("InvokeAction Error: " + errorMessage);
      Napi::TypeError::New(env, errorMessage).ThrowAsJavaScriptException();
      return env.Null();
    }
    Napi::Value instance = info[2];
    Napi::Value initialState = info[3];
    logToFile("InvokeAction proceeding with instance and initialState: ");
    std::string result = widgets[widgetId].InvokeAction(actionName, instance, initialState);
    logToFile("InvokeAction result: " + result);
    return Napi::String::New(env, result);
  }
  else if (info.Length() < 3 || !info[2].IsObject())
  {
    std::string errorMessage = "Expected instance as an argument for " + actionName;
    logToFile("InvokeAction Error: " + errorMessage);
    Napi::TypeError::New(env, errorMessage).ThrowAsJavaScriptException();
    return env.Null();
  }

  logToFile("InvokeAction proceeding with instance for actionName: " + actionName);
  std::string result = widgets[widgetId].InvokeAction(actionName);
  logToFile("InvokeAction result: " + result);

  return Napi::String::New(env, result);
}
