#include "SetSystemVolume.h"
#include <thread>
#include <chrono>
#include <atomic>

void SetSystemVolume(Napi::Env env, Napi::Function setFunction, Napi::Object instanceObj, Napi::Number volume, const std::string &deviceType, const std::string &deviceId)
{
  auto tsfn = Napi::ThreadSafeFunction::New(env, setFunction, "Set Function", 0, 1);
  std::shared_ptr<std::atomic<int>> activeCalls = std::make_shared<std::atomic<int>>(0);

  struct Context
  {
    Napi::ObjectReference jsInstance;
    double volume;
    std::string deviceType;
    std::string deviceId;
  };

  auto ctx = new Context{
      Napi::Persistent(instanceObj),
      volume.DoubleValue(),
      deviceType,
      deviceId};

  std::thread([tsfn, activeCalls, ctx]() mutable
              {
                activeCalls->fetch_add(1);
                tsfn.NonBlockingCall(ctx, [activeCalls](Napi::Env env, Napi::Function jsCallback, Context *context)
                                     {
                                             if (context->deviceType.empty() && context->deviceId.empty())
                                             {
                                                 jsCallback.Call(context->jsInstance.Value(), {Napi::Number::New(env, context->volume)});
                                             }
                                             else if (!context->deviceType.empty() && context->deviceId.empty())
                                             {
                                                 jsCallback.Call(context->jsInstance.Value(), {
                                                     Napi::Number::New(env, context->volume),
                                                     Napi::String::New(env, context->deviceType)
                                                 });
                                             }
                                             else
                                             {
                                                 jsCallback.Call(context->jsInstance.Value(), {
                                                     Napi::Number::New(env, context->volume),
                                                     Napi::String::New(env, context->deviceType),
                                                     Napi::String::New(env, context->deviceId)
                                                 });
                                             }

                                             activeCalls->fetch_sub(1); });

                while (activeCalls->load() > 0)
                {
                  std::this_thread::sleep_for(std::chrono::milliseconds(10));
                }

                tsfn.Release();
                delete ctx; })
      .detach();
}
