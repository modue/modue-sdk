#include "ActionWrapper.h"

ActionWrapper::ActionWrapper() : isValid_(false) {}

ActionWrapper::ActionWrapper(SingleParamHandler action)
    : action_(std::move(action)), isValid_(true) {}

ActionWrapper::ActionWrapper(ChangeHandler action)
    : action_(std::move(action)), isValid_(true) {}

ActionWrapper::ActionWrapper(DeactivateHandler action)
    : action_(std::move(action)), isValid_(true) {}

ActionWrapper::ActionWrapper(InitializeHandler action)
    : action_(std::move(action)), isValid_(true) {}

ActionWrapper::ActionWrapper(NotificationHandler action)
    : action_(std::move(action)), isValid_(true) {}

ActionWrapper::ActionWrapper(ConfigurationMetadata config)
    : action_(std::move(config)), isValid_(true) {}

ActionWrapper::ActionWrapper(ActionVariant action)
    : action_(std::move(action)), isValid_(true) {}

ConfigurationMetadata ActionWrapper::GetConfigurationMetadata() const
{
  if (std::holds_alternative<ConfigurationMetadata>(action_))
  {
    return std::get<ConfigurationMetadata>(action_);
  }
  throw std::runtime_error("Action is not of type ConfigurationMetadata");
}

std::string ActionWrapper::Invoke(Napi::Value instance, Napi::Number value)
{
  if (!isValid_)
  {
    return "Invalid Action";
  }

  return std::visit([instance, value](auto &&arg)
                    {
                      using T = std::decay_t<decltype(arg)>;
                      if constexpr (std::is_same_v<T, SingleParamHandler>)
                      {
                        return std::string("Action cannot be invoked with two arguments");
                      }
                      else if constexpr (std::is_same_v<T, ChangeHandler>)
                      {
                        return arg(instance, value);
                      }
                      else
                      {
                        return std::string("Unknown action type");
                      } },
                    action_);
}

std::string ActionWrapper::Invoke(Napi::Value instance, Napi::Value initialState)
{
  if (!isValid_)
  {
    return "Invalid Action";
  }

  return std::visit([instance, initialState](auto &&arg)
                    {
                      using T = std::decay_t<decltype(arg)>;
                      if constexpr (std::is_same_v<T, InitializeHandler>)
                      {
                        return arg(instance, initialState);
                      }
                      else
                      {
                        return std::string("Unknown action type");
                      } },
                    action_);
}

std::string ActionWrapper::Invoke(Napi::Value instance)
{
  if (!isValid_)
  {
    return "Invalid Action";
  }

  return std::visit([instance](auto &&arg)
                    {
                      using T = std::decay_t<decltype(arg)>;
                      if constexpr (std::is_same_v<T, SingleParamHandler>)
                      {
                        return arg(instance);
                      }
                      else if constexpr (std::is_same_v<T, ChangeHandler>)
                      {
                        return std::string("Action requires two arguments, but only one was provided");
                      }
                      else
                      {
                        return std::string("Unknown action type");
                      } },
                    action_);
}

std::string ActionWrapper::Invoke(Napi::String id)
{
  if (!isValid_)
  {
    return "Invalid Action";
  }

  return std::visit([id](auto &&arg)
                    {
                      using T = std::decay_t<decltype(arg)>;
                      if constexpr (std::is_same_v<T, DeactivateHandler>)
                      {
                          return arg(id);
                      }
                      else
                      {
                        return std::string("Unknown action type");
                      } },
                    action_);
}

std::string ActionWrapper::Invoke()
{
  if (!isValid_)
  {
    return "Invalid Action";
  }

  return std::visit([](auto &&arg)
                    {
                          using T = std::decay_t<decltype(arg)>;
                          if constexpr (std::is_same_v<T, NotificationHandler>)
                          {
                              return arg();  
                          }
                          else
                          {
                              return std::string("Unknown action type or action cannot be invoked without arguments");
                          } },
                    action_);
}
