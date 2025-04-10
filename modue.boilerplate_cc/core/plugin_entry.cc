#include <napi.h>
#include "Plugin.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports)
{
  return Plugin::Init(env, exports);
}

NODE_API_MODULE(plugin, InitAll)
