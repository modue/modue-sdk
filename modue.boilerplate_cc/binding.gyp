{
  "targets": [
    {
      "target_name": "plugin",
      "sources": [
        "core/plugin_entry.cc",
        "core/Plugin.cpp",
        "core/PluginGetConfiguration.cpp",
        "core/PluginInvokeAction.cpp",
        "core/GUIDGenerator.cpp",
        "core/ActionWrapper.cpp",
        "widget/Widget.cpp",
        "widget/WidgetActions.cpp",
        "handlers/RegisterHandlers.cpp",
        "actions/BaseEvents/Set.cpp",
        "actions/BaseEvents/SetArray.cpp",
        "actions/SystemEvents/SetSystemVolume.cpp",
        "actions/SystemEvents/MuteMicrophone.cpp",
        "actions/SystemEvents/UnmuteMicrophone.cpp",
        "actions/SystemEvents/TakeScreenshot.cpp",
        "utils/FileLogger.cpp",
      ],
      "include_dirs": [
        "<!(node -p \"require('node-addon-api').include\")",
        "./node_modules/node-addon-api",
        "."
      ],
      "dependencies": [
        "<!(node -p \"require('node-addon-api').gyp\")"
      ],
      "cflags!": ["-fno-exceptions"],
      "cflags_cc!": ["-fno-exceptions"],
      "defines": ["NAPI_EXPERIMENTAL"],
      "xcode_settings": {
        "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
        "GCC_GENERATE_DEBUGGING_SYMBOLS": "YES",
        "GCC_OPTIMIZATION_LEVEL": "0"
      },
      "msvs_settings": {
        "VCCLCompilerTool": {
          "ExceptionHandling": 1
        }
      }
    }
  ]
}
