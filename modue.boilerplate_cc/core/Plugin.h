// Plugin.h
#ifndef PLUGIN_H
#define PLUGIN_H

#include <napi.h>
#include <map>
#include <string>
#include <vector>
#include "./../widget/Widget.h"
#include "ActionWrapper.h"

class Plugin : public Napi::ObjectWrap<Plugin>
{
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  Plugin(const Napi::CallbackInfo &info);

  Napi::Value GetConfiguration(const Napi::CallbackInfo &info);
  Napi::Value InvokeAction(const Napi::CallbackInfo &info);

  void RegisterLedCluster(const std::string &name, const std::vector<std::pair<std::string, ActionWrapper>> &actions);
  void RegisterKey(const std::string &name, const std::vector<std::pair<std::string, ActionWrapper>> &actions);
  void RegisterKnob(const std::string &name, const std::vector<std::pair<std::string, ActionWrapper>> &actions);
  void RegisterSwitch(const std::string &name, const std::vector<std::pair<std::string, ActionWrapper>> &actions);
  void RegisterSlider(const std::string &name, const std::vector<std::pair<std::string, ActionWrapper>> &actions);

private:
  std::map<std::string, Widget> widgets;
};

#endif
