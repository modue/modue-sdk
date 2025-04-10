
#ifndef TAKESCREENSHOT_H
#define TAKESCREENSHOT_H

#include <napi.h>
#include <string>

void TakeScreenshot(Napi::Env env,
                    Napi::Function screenshotFunction,
                    Napi::Object instanceObj,
                    const std::string &fileName,
                    const std::string &actionName);

#endif
