#include "./../core/ActionWrapper.h"
#include <map>
#include <string>
#include <vector>
#include <list>

class Widget
{
public:
  Widget(); // Default constructor
  Widget(std::string name, std::string type);

  Widget(const Widget &other);

  Widget(Widget &&other) noexcept;

  Widget &operator=(const Widget &other);

  Widget &operator=(Widget &&other) noexcept;

  void RegisterAction(const std::string &actionName, ActionWrapper action);

  std::string InvokeAction(const std::string &actionName);
  std::string InvokeAction(const std::string &actionName, Napi::Value instance);
  std::string InvokeAction(const std::string &actionName, Napi::String id);
  std::string InvokeAction(const std::string &actionName, Napi::Value instance, Napi::Number value);
  std::string InvokeAction(const std::string &actionName, Napi::Value instance, Napi::Value initialState);

  std::vector<ActionWrapper> GetActions(const std::string &actionName);

  std::string GetName() const;
  std::string GetType() const;
  std::vector<std::string> GetImplementedActions() const;

private:
  std::string name_;
  std::string type_;
  std::multimap<std::string, ActionWrapper> actions_;
};
