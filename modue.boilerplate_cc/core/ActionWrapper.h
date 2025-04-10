#ifndef ACTIONWRAPPER_H
#define ACTIONWRAPPER_H

#include <variant>
#include <functional>
#include <string>
#include <napi.h>

using SingleParamHandler = std::function<std::string(Napi::Value)>;
using ChangeHandler = std::function<std::string(Napi::Value, Napi::Number)>;
using DeactivateHandler = std::function<std::string(Napi::String)>;
using InitializeHandler = std::function<std::string(Napi::Value, Napi::Value)>;
using NotificationHandler = std::function<std::string()>;

struct ConfigurationMetadata
{
  std::string key;
  std::string name;
  std::string description;
  std::string type;
};

using ActionVariant = std::variant<SingleParamHandler, ChangeHandler, DeactivateHandler, InitializeHandler, NotificationHandler, ConfigurationMetadata>;

class ActionWrapper
{
public:
  ActionWrapper();
  explicit ActionWrapper(SingleParamHandler action);
  explicit ActionWrapper(ChangeHandler action);
  explicit ActionWrapper(DeactivateHandler action);
  explicit ActionWrapper(InitializeHandler action);

  explicit ActionWrapper(NotificationHandler action);

  explicit ActionWrapper(ConfigurationMetadata config);

  explicit ActionWrapper(ActionVariant action);

  std::string Invoke(Napi::Value instance);
  std::string Invoke(Napi::String id);
  std::string Invoke();
  std::string Invoke(Napi::Value instance, Napi::Number value);
  std::string Invoke(Napi::Value instance, Napi::Value value);

  ConfigurationMetadata GetConfigurationMetadata() const;

private:
  ActionVariant action_;
  bool isValid_;
};

#endif
