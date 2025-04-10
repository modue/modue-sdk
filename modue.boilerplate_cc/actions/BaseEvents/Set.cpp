#include "Set.h"
#include <napi.h>
#include <thread>
#include <chrono>
#include <atomic>

void Set(Napi::Env env, Napi::Function setFunction, Napi::Object instanceObj, double value, const std::string &actionName)
{
  auto tsfn = Napi::ThreadSafeFunction::New(env, setFunction, "Set Function", 0, 1);
  std::shared_ptr<std::atomic<int>> activeCalls = std::make_shared<std::atomic<int>>(0);

  struct Context
  {
    Napi::ObjectReference jsInstance;
    std::string actionName;
    double value; // Capture the value
  };

  auto ctx = new Context{
      Napi::Persistent(instanceObj),
      actionName,
      value // Pass the value into the context
  };

  std::thread([tsfn, activeCalls, ctx]() mutable
              {
                activeCalls->fetch_add(1);

                tsfn.NonBlockingCall(ctx, [activeCalls](Napi::Env env, Napi::Function jsCallback, Context *context)
                                     {
            jsCallback.Call(context->jsInstance.Value(), {Napi::Number::New(env, context->value)});

            activeCalls->fetch_sub(1); });

                while (activeCalls->load() > 0)
                {
                  std::this_thread::sleep_for(std::chrono::milliseconds(10));
                }

                tsfn.Release();
                delete ctx; })
      .detach();
}
