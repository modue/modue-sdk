# Proof of Concept: Integration of JavaScript and C++ in Plugin Development

## Overview
This Proof of Concept (PoC) demonstrates how to integrate a JavaScript-based SDK with a C++ logic layer in an Electron-based application. The goal was to showcase the flexibility of the SDK by extending plugin functionality using C++. The solution effectively bridges JavaScript and C++ using **node-gyp** and **N-API**.

## Technology Stack
- **Electron** for the main application interface
- **Node.js** for backend logic within the plugin
- **TypeScript/JavaScript** for SDK structure and plugin interface
- **C++** for core logic execution
- **node-gyp** for compiling native C++ code as a Node.js module
- **N-API** for creating a native Node.js addon

## Architecture

### JavaScript Layer
The JavaScript layer acts as an interface between the Electron app and the underlying C++ logic. It:
- Defines and registers widgets via SDK methods
- Establishes mappings between widget events and C++ logic
- Ensures proper data flow from JavaScript to C++

### Key JavaScript Components

**`index.js` (Plugin Entry Point)**
- Loads the compiled C++ addon using `require('bindings')('plugin')`
- Iterates through the available widgets defined by the C++ layer
- Dynamically registers widget actions like `registerOnChangeHandler`, `registerOnInitializeHandler`, etc.
- Uses `createInstance.js` to wrap JavaScript instances with additional logic when interacting with C++

**`createInstance.js`**
- Provides enhanced JavaScript instances with utility methods for handling common system actions like:
  - `setSystemVolume`
  - `openApp`
  - `muteMicrophone`
  - `takeScreenshot`
  - `pressKeystrokes`
- Acts as a middleware layer, ensuring JS instances pass correctly formatted data to the C++ backend

**`registerSystemActions.js`**
- Defines system-level handlers for additional plugin functionality
- Handles actions like:
  - `useSystemMuteMicrophone`
  - `useSystemInstalledApps`
  - `useSystemVolume`

**`widgetConfiguration.js`**
- Manages the dynamic configuration of widgets, including adding inputs, dropdowns, and buttons

### C++ Layer
The C++ logic layer is implemented as a Node.js addon compiled with `node-gyp`. The addon is exposed via the `bindings` package.

**`Plugin.cpp`**
- Implements the core logic of the plugin
- Uses **N-API** to expose functions that JavaScript can invoke
- Defines multiple widgets with corresponding handlers:
  - **Sliders**
  - **Keys**
  - **Knobs**
  - **Switches**
  - **LED Clusters**
- Each widget includes a set of mapped actions for various handlers like `registerOnChangeHandler` or `registerOnInitializeHandler`
- The plugin logic relies on mapping actions to handler functions defined in the C++ code

### RegisterHandlers Implementation
The `RegisterHandlers` component provides core logic for handling various actions. Key functions include:

- **`RegisterOnInitializeHandlerLed`** – Initializes LED clusters and assigns random colors.
- **`RegisterOnInitializeHandler`** – Basic initialization for widgets.
- **`RegisterOnConfigurationChangeHandler`** – Handles configuration changes with flexible value parsing.
- **`RegisterAppsOrDeviceList`** – Serializes a provided object or array for apps or devices.
- **`RegisterResourceHandler`** – Monitors CPU usage and visualizes load using LED clusters.
- **`RegisterOnKeyDownHandler`** and **`RegisterOnKeyUpHandler`** – Manage key press events.
- **`RegisterMuteUnmuteOnKeyDownHandler`** – Randomly toggles between mute and unmute states.
- **`RegisterTakeScreenshotHandler`** – Captures a screenshot with a randomly generated filename.
- **`RegisterControlSystemMediaPlayerHandler`** – Simulates media control actions like play/pause, next, and previous.
- **`RegisterOpenChromeAppHandler`** – Launches Chrome using the `openApp` API.

### Key Action Implementations
**`Set.cpp`**
- Utilizes `Napi::ThreadSafeFunction` to ensure thread safety when interacting with JavaScript functions.
- Handles asynchronous calls for setting values within the plugin architecture.

**`MuteMicrophone.cpp`**
- Similar to `Set.cpp`, leverages `Napi::ThreadSafeFunction` to manage asynchronous mute actions securely.

### Key Integration Flow
1. The Electron app loads the plugin by importing the JavaScript entry point (`index.js`).
2. The plugin dynamically identifies widgets and their associated actions by invoking the C++ plugin's `getConfiguration()` method.
3. For each identified widget, the plugin registers handlers and assigns an instance to the widget via the `createInstance()` utility.
4. When an event occurs (e.g., `onChange`, `onKeyDown`), the respective JavaScript handler delegates the logic to the C++ layer using the `invokeAction()` method.
5. The C++ logic processes the event and returns the result back to the JavaScript layer, which logs the outcome for further handling or visualization.

## Example Widget Registration Flow
- The C++ plugin defines a widget with the following logic:
```cpp
this->RegisterSlider("System API - speaker volume",
  {{ActionToString(KeyActions::RegisterOnInitializeHandler), ActionWrapper(SingleParamHandler(RegisterOnInitializeHandler))},
   {ActionToString(SliderActions::RegisterOnChangeHandler), ActionWrapper(ChangeHandler(RegisterVolumeOnChangeHandler))},
   {ActionToString(SystemActions::UseSystemVolume), ActionWrapper(ChangeHandler(UseSystemVolumeHandler))},
   {ActionToString(KeyActions::RegisterOnDeactivateHandler), ActionWrapper(DeactivateHandler(RegisterOnDeactivateHandler))}});
```

- The JavaScript logic maps the C++ actions and registers the respective handlers:
```javascript
if (widgetActions.includes('registerOnChangeHandler')) {
  widget.registerOnChangeHandler((value, instance) => {
    const cppInstance = assignInstance(instance, 'registerOnChangeHandler');
    const result = cppPlugin.invokeAction(widgetId, 'registerOnChangeHandler', cppInstance, value);
    log.info(result);
  });
}
```

## Key Benefits
- Demonstrates how the SDK can be extended using technologies other than JavaScript
- Maintains seamless integration with Electron-based UI while offloading logic to C++ for improved performance
- Ensures flexible and scalable plugin architecture by bridging different languages

## Future Improvements
- Enhance error handling between the JavaScript and C++ layers
- Improve the configuration system for easier widget customization
- Introduce more comprehensive logging and debugging tools for both JS and C++ layers

## Conclusion
This PoC successfully demonstrates how to extend the SDK with C++ logic using **node-gyp** and **N-API**. The design allows developers to integrate performance-critical features into the application while maintaining flexibility through JavaScript interfaces.

