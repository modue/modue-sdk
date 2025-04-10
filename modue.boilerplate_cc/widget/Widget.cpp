#include "Widget.h"

Widget::Widget() : name_(""), type_("") {}

Widget::Widget(std::string name, std::string type)
    : name_(std::move(name)), type_(std::move(type)) {}

Widget::Widget(const Widget &other)
    : name_(other.name_), type_(other.type_), actions_(other.actions_) {}

Widget::Widget(Widget &&other) noexcept
    : name_(std::move(other.name_)), type_(std::move(other.type_)), actions_(std::move(other.actions_)) {}

Widget &Widget::operator=(const Widget &other)
{
  if (this != &other)
  {
    name_ = other.name_;
    type_ = other.type_;
    actions_ = other.actions_;
  }
  return *this;
}

Widget &Widget::operator=(Widget &&other) noexcept
{
  if (this != &other)
  {
    name_ = std::move(other.name_);
    type_ = std::move(other.type_);
    actions_ = std::move(other.actions_);
  }
  return *this;
}

void Widget::RegisterAction(const std::string &actionName, ActionWrapper action)
{
  actions_.emplace(actionName, std::move(action));
}

std::string Widget::InvokeAction(const std::string &actionName)
{
  auto actions = GetActions(actionName);
  if (!actions.empty())
  {
    return actions.front().Invoke();
  }
  return "Action not implemented";
}

std::string Widget::InvokeAction(const std::string &actionName, Napi::Value instance)
{
  auto actions = GetActions(actionName);
  if (!actions.empty())
  {
    return actions.front().Invoke(instance);
  }
  return "Action not implemented";
}

std::string Widget::InvokeAction(const std::string &actionName, Napi::String id)
{
  auto actions = GetActions(actionName);
  if (!actions.empty())
  {
    return actions.front().Invoke(id);
  }
  return "Action not implemented";
}

std::string Widget::InvokeAction(const std::string &actionName, Napi::Value instance, Napi::Number value)
{
  auto actions = GetActions(actionName);
  if (!actions.empty())
  {
    return actions.front().Invoke(instance, value);
  }
  return "Action not implemented";
}

std::string Widget::InvokeAction(const std::string &actionName, Napi::Value instance, Napi::Value initialState)
{
  auto actions = GetActions(actionName);
  if (!actions.empty())
  {
    return actions.front().Invoke(instance, initialState);
  }
  return "Action not implemented";
}

std::string Widget::GetName() const
{
  return name_;
}

std::string Widget::GetType() const
{
  return type_;
}

std::vector<std::string> Widget::GetImplementedActions() const
{
  std::vector<std::string> implementedActions;
  for (const auto &actionPair : actions_)
  {
    implementedActions.push_back(actionPair.first);
  }
  return implementedActions;
}

std::vector<ActionWrapper> Widget::GetActions(const std::string &actionName)
{
  std::vector<ActionWrapper> matchingActions;
  auto range = actions_.equal_range(actionName);
  for (auto it = range.first; it != range.second; ++it)
  {
    matchingActions.push_back(it->second);
  }
  return matchingActions;
}
