#include "Plugin.h"

Napi::Value Plugin::GetConfiguration(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Object config = Napi::Object::New(env);

  for (const auto &widgetPair : widgets)
  {
    Napi::Object widgetInfo = Napi::Object::New(env);
    widgetInfo.Set("name", widgetPair.second.GetName());
    widgetInfo.Set("type", widgetPair.second.GetType());

    Napi::Array actionArray = Napi::Array::New(env);
    int index = 0;
    for (const auto &actionName : widgetPair.second.GetImplementedActions())
    {
      actionArray.Set(index++, actionName);
    }
    widgetInfo.Set("actions", actionArray);

    config.Set(widgetPair.first, widgetInfo);
  }

  return config;
}
