#include "UnmuteMicrophone.h"
#include <napi.h>
#include <thread>
#include <chrono>
#include <atomic>

void UnmuteMicrophone(Napi::Env env, Napi::Function unmuteFunction, Napi::Object instanceObj, const std::string &actionName)
{
  auto tsfn = Napi::ThreadSafeFunction::New(env, unmuteFunction, "Unmute Function", 0, 1);
  std::shared_ptr<std::atomic<int>> activeCalls = std::make_shared<std::atomic<int>>(0);

  struct Context
  {
    Napi::ObjectReference jsInstance;
    std::string actionName;
  };

  auto ctx = new Context{
      Napi::Persistent(instanceObj),
      actionName};

  std::thread([tsfn, activeCalls, ctx]() mutable
              {
                activeCalls->fetch_add(1);

                tsfn.NonBlockingCall(ctx, [activeCalls](Napi::Env env, Napi::Function jsCallback, Context *context)
                                     {
            jsCallback.Call(context->jsInstance.Value(), {});

            activeCalls->fetch_sub(1); });

                while (activeCalls->load() > 0)
                {
                  std::this_thread::sleep_for(std::chrono::milliseconds(10));
                }

                tsfn.Release();
                delete ctx; })
      .detach();
}
