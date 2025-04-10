#include "SetArray.h"
#include "./../../utils/FileLogger.h"
#include <thread>
#include <chrono>
#include <atomic>

void SetArray(Napi::Env env, Napi::Function setFunction, Napi::Object instanceObj, const std::string &actionName, const std::vector<std::string> &ledsToFlash)
{
  auto tsfn = Napi::ThreadSafeFunction::New(env, setFunction, "Set Function", 0, 1);
  std::shared_ptr<std::atomic<int>> activeCalls = std::make_shared<std::atomic<int>>(0);

  struct Context
  {
    Napi::ObjectReference jsInstance;
    std::string actionName;
    std::vector<std::string> ledsToFlash;
  };

  auto ctx = new Context{
      Napi::Persistent(instanceObj),
      actionName,
      ledsToFlash};

  std::thread([tsfn, activeCalls, ctx]() mutable
              {
                activeCalls->fetch_add(1);

                tsfn.BlockingCall(ctx, [activeCalls](Napi::Env env, Napi::Function jsCallback, Context *context)
                                  {
            Napi::HandleScope scope(env);

            Napi::Array ledArray = Napi::Array::New(env, context->ledsToFlash.size());
            for (size_t i = 0; i < context->ledsToFlash.size(); ++i)
            {
                ledArray.Set(i, Napi::String::New(env, context->ledsToFlash[i]));
            }

            jsCallback.Call(context->jsInstance.Value(), {ledArray});

            activeCalls->fetch_sub(1); });

                while (activeCalls->load() > 0)
                {
                  std::this_thread::sleep_for(std::chrono::milliseconds(10));
                }

                tsfn.Release();
                delete ctx; })
      .detach();
}
