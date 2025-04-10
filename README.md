<br>

# Table of Contents  

1. [Plugins](#plugins)
    * [Plugin configuration](#pluginConfiguration)
    * [Register Slider Widget](#registerSliderWidget)
    * [Register Key Widget](#registerKeyWidget)
    * [Register Knob Widget](#registerKnobWidget)
    * [Register Led cluster Widget](#registerLedClusterWidget)
    * [Register Display widget](#registerDisplayWidget)
      * [Display element](#displayElement)
      * [Display slider](#displaySlider)
      * [Display text](#displayText)
      * [Display image](#displayImage)
    * [Widgets base API](#widgetsBaseAPI)
    * [Widgets system API](#widgetsSystemAPI)
      * [Widgets windows API](#widgetsSystemWindowsAPI)
    * [Instances](#instances)
    * [Widgets configuration API](#widgetsConfigurationAPI)
    * [Widgets events](#widgetsEvents)
    * [Plugin configuration API](#pluginConfigurationAPI)
    * [Plugin storage API](#pluginStorageAPI)
    * [Internationalization i18n - transaltions](#translations)
    * [DevTools log](#devToolsLog)
    * [Plugin messages API](#messages)
    * [Changelog](#changelog)

# Plugins

modue plugins structure:

```
project
|
└─── plugins
|   |
|   └─── plugin1
|   |   |   package.json
|   |   |   index.js
|   |   |
|   |
|   └─── plugin2
|   |
|   ...
|   |
|   └─── pluginN
```

***package.json*** file structure:

```json
{
  "name": "@modue/somePluginName",
  "version": "1.0.0",
  "description": "Example description",
  "main": "index.js", // executable file, can be index.js or another
  "author": "modue developer",
  "license": "ISC",
  "os": "darwin", // darwin | win32, if not setted plugin is multiplatform
  "keywords": ["some", "package", "keywords", "darwin"], // use to search package in feed, also use to filter package target platform
  "devMode": true, // devMode enable fast plugin reload by Crtl/Cmd + Shift + R or in menu action and show full plugin config in plugins view
}

```

example of plugin script

```js
export default (configuration, storage, log) => {
  configuration.registerSlider({ name: 'changeVolumeWidget' });
  configuration.registerSlider({ name: 'changeSensitivitytWidget' });
};

```

## Plugin configuration - configuration object <a id="pluginConfiguration"></a>

The configuration object is injected into default function exported from the plugin. Plugin configuration is done using fluent API.

### Widget instance

```ts
enum DeviceType {
  SPEAKERS = 'Speakers',
  MIKE = 'Mike',
}

enum PlayerCommand {
  NEXT = 'next',
  PREVIOUS = 'previous',
  PLAYPAUSE = 'play/pause"',
}

interface AvailableAudioApplication {
  id: number;
  name: string;
  icon: string;
  volume: number;
}

interface InstalledApplication {
  id: string;
  name: string;
}

interface AvailableDevice {
  id: string;
  name: string;
  device_type: DeviceType;
}

export enum SwitchDirection {
  LEFT = 'Left',
  RIGHT = 'Right',
}

export enum DeviceType {
  SPEAKERS = 'Speakers',
  MIKE = 'Mike',
}

export enum PlayerCommand {
  NEXT = 'next',
  PREVIOUS = 'previous',
  PLAYPAUSE = 'play/pause',
}

export enum CycleDirection {
  FORWARD = 'Forward',
  BACKWARD = 'Backward',
}

export enum ScrollDirection {
  UP = 'Up',
  DOWN = 'Down',
  LEFT = 'Left',
  RIGHT = 'Right',
}

export enum ZoomDirection {
  IN = 'In',
  OUT = 'Out',
}

interface IWidgetInstance {
  id: string // guid format
  name: string;
  numberOfLeds: number;

  isActive: boolean;

  set?: (value: unknown) => void; // value depends of widget type, check in widgets
  sendEvent?: (value: unknown) => void;

  applications: InstalledApplication[];
  availableAudioApplications: AvailableAudioApplication[];
  microphones: AvailableDevice[];
  speakers: AvailableDevice[];
  
  configuration?: {
    [key: string]: any;
  }

  components?: { // display components
    [name: string]: { // the name from component configuration
        set?: (value: unknown) => void; // value depends of widget type, check in display widgets
        sendEvent?: (value: unknown) => void;
    }
  }

  setSystemVolume?: (volume: number, deviceType: DeviceType, deviceId: string) => void;
  openApp?: (appId: string) => void;
  muteMicrophone?: (deviceId: string) => void;
  unmuteMicrophone?: (deviceId: string) => void;
  setSwitchVirtualDesktop?: (side: SwitchDirection) => void;
  setSystemOutputMute?: (value: boolean) => void;
  takeScreenshot?: (saveLocation: string) => void;
  setControlSystemMediaPlayer?: (playerAction: PlayerCommand) => void;
  pressKeystrokes?: (keyCodes: number[], applicationId?: string) => void;

  windows?: {
    setAppVolume?: (volume: number, applicationId: string) => void;
    setCycleAppWindows?: (value: CycleDirection) => void;
    setCycleBrowserTab?: (value: CycleDirection) => void;
    setOpenPath?: (locationPath: string) => void;
    setScroll?: (scrollDirection: ScrollDirection, scrollSpeed: number) => void;
    setChooseInputDevice?: (deviceId: string) => void;
    setChooseOutputDevice?: (deviceId: string) => void;
    setMuteApp?: (applicationId: string) => void;
    setUnmuteApp?: (applicationId: string) => void;
    setScreenBrightness?: (brightness: number) => void;
    setZoom?: (zoomDirection: ZoomDirection) => void;
  };
}
```

### Widget initial state

> [!WARNING]
> **ISDKWidgetInitialState** is no longer supported. The same information are available in **IWidgetInstance**.

```ts
interface ISDKWidgetInitialState {
    audioAvailableApps: AvailableAudioApplication[];
    apps: InstalledApplication[];
    microphones: AvailableDevice[];
    speakers: AvailableDevice[];
    configuration: {
      [key: string]: any;
    };
}
``

### Plugin platform

```ts
enum PLUGIN_PLATFORM {
  MACOS = 'darwin',
  WINDOWS = 'win32'
}
```

## Register Slider Widget <a id="registerSliderWidget"></a>

<table>
<thead>

<tr>
<th> Name </th> <th> Arguments </th> <th> Description </th>
</tr>
</thead>
<tbody>
<tr>
<td>

**registerSlider**

</td>
<td>

`sliderProps: Object, platform?: PLUGIN_PLATFORM`

</td>
<td>

Register slider widget

Definition:

```js
{
    name: string,
}
```

</td>
</tr>
</tbody>
</table>

```js
export default (configuration) => {
  configuration.registerSlider({ name: 'changeVolumeWidget' });
};
```

```js
export default (configuration) => {
  configuration.registerSlider({ name: 'OnlyWindowsVolumeWidget' }, 'win32');
};
```

Slider widget functions

| Name | Arguments | Description |
|------|-----------|-------------|
| **registerOnChangeHandler** | `handler: func` | Register handler invoked when slider value changed <br><br>  Definition:<br> ```function(value: number, instance IWidgetInstance) => void``` |

### Examples

Add on change handler to slider widget

```js
configuration.registerSlider(...)
  .registerOnChangeHandler((value) => {
    // slider value on Device has been changed!
  });
```

## Register Key Widget <a id="registerKeyWidget"></a>

<table>
<thead>

<tr>
<th> Name </th> <th> Arguments </th> <th> Description </th>
</tr>
</thead>
<tbody>
<tr>
<td>

**registerKey**

</td>
<td>

`keyProps: Object, platform?: PLUGIN_PLATFORM`

</td>
<td>

Register key widget

Definition:

```js
{
    name: string,
}
```

</td>
</tr>
</tbody>
</table>

```js
export default (configuration) => {
  configuration.registerKey({ name: 'keyWidget' });
};
```

Key widget functions

| Name | Arguments | Description |
|------|-----------|-------------|
| **registerOnKeyUpHandler** | `handler: func` | Register handler invoked when the key has been upped <br><br>  Definition:<br> ```function(instance IWidgetInstance) => void``` |
| **registerOnKeyDownHandler** | `handler: func` | Register handler invoked when the key has been downed <br><br>  Definition:<br> ```function(instance IWidgetInstance) => void``` |

### Examples

#### Add on key up handler to key widget

```js
configuration.registerKey(...)
  .registerOnKeyUpHandler(() => {
    // key on Device has been upped
  });
```

#### Add on key down handler to key widget

```js
configuration.registerKey(...)
  .registerOnKeyDownHandler(() => {
    // key on Device has been downed
  });
```

## Register Knob Widget <a id="registerKnobWidget"></a>

<table>
<thead>

<tr>
<th> Name </th> <th> Arguments </th> <th> Description </th>
</tr>
</thead>
<tbody>
<tr>
<td>

**registerKnob**

</td>
<td>

`knobProps: Object, platform?: PLUGIN_PLATFORM`

</td>
<td>

Register knob widget

Definition:

```js
{
    name: string,
}
```

</td>
</tr>
</tbody>
</table>

```js
export default (configuration) => {
  configuration.registerKnob({ name: 'changeVolumeWidget' });
};
```

Knob widget functions

| Name | Arguments | Description |
|------|-----------|-------------|
| **registerOnChangeHandler** | `handler: func` | Register handler invoked when knob value changed <br><br>  Definition:<br> ```function(value: number, instance IWidgetInstance) => void``` |

### Examples

Add on change handler to slider widget

```js
configuration.registerKnob(...)
  .registerOnChangeHandler((value) => {
    // slider value on Device has been changed!
  });
```

## Register Led cluster Widget <a id="registerLedClusterWidget"></a>

<table>
<thead>

<tr>
<th> Name </th> <th> Arguments </th> <th> Description </th>
</tr>
</thead>
<tbody>
<tr>
<td>

**registerLedCluster**

</td>
<td>

`ledClusterProps: Object, platform?: PLUGIN_PLATFORM`

</td>
<td>

Register led cluster widget

Definition:

```js
{
    name: string,
}
```

</td>
</tr>
</tbody>
</table>

```js
export default (configuration) => {
  configuration.registerLedCluster({ name: 'Led cluster' });
};
```

Led cluster widget extends `IWidgetInstance` by `numberOfLeds` property which returns physical number of widget leds.

```ts

type LedValue =  string | null;

IWidgetInstance {
  ...
  numberOfLeds: number,
  set: (value: LedValue[]) => void; // value should be array of led values, all values over limit will be ignored.
}
```

### Examples

#### Random set leds on initialize

```js
configuration
    .registerLedCluster(...)
    .registerOnInitializeHandler((instance) => {
      const ledsToFlash = Array.from(Array(instance.numberOfLeds)).map(() => {
        if (Math.random() > 0.5) {
          return "#FF0000FF"; // set color to red (in decimal: R = 255, G = 0, B = 0, Brightnes = 255)
          // Color must be string representing a color in hex code for Red, Green, Blue channels (RGB) and brightnes
        }

        return null; // null value turns off a LED
      });

      instance.set(ledsToFlash); // Flash LEDs
    })
```

#### Set leds based on system volume

```js
.registerLedCluster(...)
    .useSystemVolume((value, instance) => {
      const numberOfLeds = instance.numberOfLeds;
      const ledsToFlash = Array.from(Array(instance.numberOfLeds)).map((_, index) => {
          if(value > index/numberOfLeds * 100){ // volume value comapred to an index normalized to a value between 0 and 100
            return "#FFFFFFFF" // Color white 
          }
          return null;
        });
      instance.set(ledsToFlash);
    });
```

## Register Display Widget <a id="registerDisplayWidget"></a>

<table>
<thead>

<tr>
<th> Name </th> <th> Arguments </th> <th> Description </th>
</tr>
</thead>
<tbody>
<tr>
<td>

**registerDisplay**

</td>
<td>

`displayProps: Object, platform?: PLUGIN_PLATFORM`

</td>
<td>

Register display widget

Definition:

```js
{
    name: string,
}
```

</td>
</tr>
</tbody>
</table>

```js
export default (configuration) => {
  configuration.registerDisplay({ name: 'displayButtonWidget' });
};
```

Display functions

| Name | Arguments | Description |
|------|-----------|-------------|
| **setSize** | `x: number, y: number` | Set size of display component. Max `x` value is `2`, max `y` value is `8`. Minimum tile size is 60px x 60px. |
| **addLayer** | `createLayer: func` | Create display layer. Layers are printed from (0, 0) coordinates. Next layer is over previous layer.  <br><br>  Definition:<br> ```function(layer: DisplayElementSDK) => void```

### Display element (DisplayElementSDK) <a id="displayElement"></a>

<table>
<thead>
<tr>
<th> Name </th> <th> Arguments </th> <th> Description </th>
</tr>
</thead>
<tbody>
<tr>
<td>

**addRow**

</td>
<td>

`displayLayoutElementCreator: func`

</td>
<td>

Create row structure. Elements in row are rendered from left to right. <br><br>  Definition:<br>
```js
function(row: DisplayElementSDK) => void
```

</td>
</tr>
<tr>
<td>

**addColumn**

</td>
<td>

`displayLayoutElementCreator: func`

</td>
<td>

Create column structure. Elements in column are rendered from top to bottom. <br><br>  Definition:<br> 
```js
function(column: DisplayElementSDK) => void
```

</td>
</tr>
<tr>
<td>

**addDisplaySlider**

</td>
<td>

`name: string, displaySliderCreator: func`

</td>
<td>

Create display slider structure. <br><br>  Definition: <br> 
```js
function(displaySlider: DisplaySliderSDK) => void
```

</td>
</tr>
<tr>
<td>

**addDisplayText**

</td>
<td>

`name: string, displayTextCreator: func`

</td>
<td>

Create display text structure. <br><br>  Definition:<br> 
```js
function(displayText: DisplayTextSDK) => void
```

</td>
</tr>
<tr>
<td>

**addDisplayImage**

</td>
<td>

`name: string, displayImageCreator: func`

</td>
<td>

Create display image structure. <br><br>  Definition:<br> 
```js
function(displaySlider: DisplayImageSDK) => void
```

</td>
</tr>
<tr>
<td>

**setSize**

</td>
<td>

`x: number, y: number`

</td>
<td>

Set size of display element. Max `x` value is `120px`, max `y` value is `960px`.

</td>
</tr>
<tr>
<td>

**setBackgroundColor**

</td>
<td>

`value: string`

</td>
<td>

Set background color ```hex format ex. #111111```

</td>
</tr>
<tr>
<td>

**setMargin**

</td>
<td>

`top: number | 'auto', right: number | 'auto', bottom: number | 'auto', left: number | 'auto'`

</td>
<td>

Set element margin.

</td>
</tr>
<tr>
<td>

**setBorderRadius**

</td>
<td>

`topLeft: number, topRight: number, bottomRight: number, bottomLeft: number'`

</td>
<td>

Set element border radius.

</td>
</tr>
<tr>
<td>

**registerOnTouchStartHandler**

</td>
<td>

`handler: func`

</td>
<td>

Register handler, invoked when element touch has been started. <br><br>  Definition:<br> 
```js
function(instance IWidgetInstance) => void
```

</td>
</tr>
<tr>
<td>

**registerOnTouchEndHandler**

</td>
<td>

`handler: func`

</td>
<td>

Register handler, invoked when element touch has been ended. <br><br>  Definition:<br> 
```js
function(instance IWidgetInstance) => void
```

</td>
</tr>
<tr>
<td>

**registerOnTouchMoveHandler**

</td>
<td>

`handler: func`

</td>
<td>

Register handler, invoked when touch on the element has been moved. <br><br>  Definition:<br> 
```js
function(
  value: {
    deltaX: number,
    deltaY: number
  },
  instance IWidgetInstance
) => void
```

</td>
</tr>
</tbody>
</table>

### Display slider - Component (DisplaySliderSDK) <a id="displaySlider"></a>

<table>
<thead>
<tr>
<th> Name </th> <th> Arguments </th> <th> Description </th>
</tr>
</thead>
<tbody>
<tr>
<td>

**setBackgroundColor**

</td>
<td>

`value: string`

</td>
<td>

Set slider background color ```hex format ex. #363636```

</td>
</tr>
<tr>
<td>

**setColor**

</td>
<td>

`value: string`

</td>
<td>

Set slider track color ```hex format ex. #ffffff```

</td>
</tr>
<tr>
<td>

**setIcon**

</td>
<td>

`value: string`

</td>
<td>

Set slider icon. You can set any material symbols icon. Icon should be lowercase and spaces replaced by underscore sign '_'

</td>
</tr>
</tr>
<tr>
<td>

**setIconColor**

</td>
<td>

`value: string`

</td>
<td>

Set slider icon color ```hex format ex. #000000```

</td>
</tr>
<tr>
<td>

**setIconBackgroundColor**

</td>
<td>

`value: string`

</td>
<td>

Set slider background icon color (icon under track, used to improve visibility of icon) ```hex format ex. #ffffff```

</td>
</tr>
<tr>
<td>

**setOrientation**

</td>
<td>

`value: 'horizontal' | 'veritcal'`

</td>
<td>

Set slider orientation

</td>
</tr>
<tr>
<td>

**registerOnChangeHandler**

</td>
<td>

`handler: func`

</td>
<td>

Register handler, invoked when slider value has been changed. The slider operates on values ​​in the range: 0 - 100. <br><br>  Definition:<br> 
```js
function(value: number, instance IWidgetInstance) => void
```

</td>
</tr>
<tr>
<td>

**setSize**

</td>
<td>

`x: number, y: number`

</td>
<td>

Set size of display element. Max `x` value is `120px`, max `y` value is `960px`.

</td>
</tr>
<tr>
<td>

**setMargin**

</td>
<td>

`top: number | 'auto', right: number | 'auto', bottom: number | 'auto', left: number | 'auto'`

</td>
<td>

Set element margin.

</td>
</tr>
<tr>
<td>

**setBorderRadius**

</td>
<td>

`topLeft: number, topRight: number, bottomRight: number, bottomLeft: number`

</td>
<td>

Set element border radius.

</td>
</tr>
<tr>
<td>

**registerOnTouchStartHandler**

</td>
<td>

`handler: func`

</td>
<td>

Register handler, invoked when screen touch has been started. Override base **registerOnChangeHandler** behavior. On change handler will not work when touchStart handler is defined. <br><br>  Definition:<br> 
```js 
function(instance IWidgetInstance) => void
```

</td>
</tr>
<tr>
<td>

**registerOnTouchEndHandler**

</td>
<td>

`handler: func`

</td>
<td>

Register handler, invoked when screen touch has been ended. Override base **registerOnChangeHandler** behavior. On change handler will not work when touchEnd handler is defined. <br><br> Definition:<br>
```js 
function(instance IWidgetInstance) => void
```

</td>
</tr>
<tr>
<td>

**registerOnTouchMoveHandler**

</td>
<td>

`handler: func`

</td>
<td>

Register handler, invoked when touch on the screen has been moved. Override base **registerOnChangeHandler** behavior. On change handler will not work when touchMove handler is defined. <br><br>  Definition:<br> 
```js
function(
  value: {
    deltaX: number,
    deltaY: number
  },
  instance IWidgetInstance
) => void
```

</td>
</tr>
</tbody>
</table>

> <br> **Instance information:** <br><br> If display slider is defined `IWidgetInstance` components collection will be extended by this component. <br><br>

### Display text - Component (DisplayTextSDK) <a id="displayText"></a>

<table><thead>
<tr>
<th> Name </th> <th> Arguments </th> <th> Description </th>
</tr>
</thead>
<tbody>
<tr>
<td>

**setColor**

</td>
<td>

`value: string`

</td>
<td>

Set text color ```hex format ex. #ffffff```

</td>
</tr>
<tr>
<td>

**setBackgroundColor**

</td>
<td>

`value: string`

</td>
<td>

Set background color ```hex format ex. #363636```

</td>
</tr>
<tr>
<td>

**setText**

</td>
<td>

`value: string`

</td>
<td>

Set text in component. Can be override from component object in `instance` by `set` function.

</td>
</tr>
<tr>
<td>

**setFontSize**

</td>
<td>

`value: number`

</td>
<td>

Set font size.

</td>
</tr>
<tr>
<td>

**setFontFace**

</td>
<td>

`value: string`

</td>
<td>

Set font face *** This function is not available at the moment. We support only default font face. ***

</td>
</tr>
<tr>
<td>

**setLetterSpacing**

</td>
<td>

`value: number`

</td>
<td>

Set letter spacing.

</td>
</tr>
<tr>
<td>

**setLineHeight**

</td>
<td>

`value: number`

</td>
<td>

Set line height.

</td>
</tr>
<tr>
<td>

**setFontStyle**

</td>
<td>

`value: 'underline' | 'italic`

</td>
<td>

Set font style.

</td>
</tr>
<tr>
<td>

**setFontWeight**

</td>
<td>

`value: bold' | 'light'`

</td>
<td>

Set font weight.

</td>
</tr>
<tr>
<td>

**setTextWrap**

</td>
<td>

`value: 'wrap' | 'clip' | 'ellipsis'`

</td>
<td>

Set text wrap.

</td>
</tr>
<tr>
<td>

**setTextAlign**

</td>
<td>

`value: 'left' | 'center' | 'right'`

</td>
<td>

Set text align.

</td>
</tr>
<tr>
<td>

**setIsIcon**

</td>
<td>

`value: boolean`

</td>
<td>

If setted, entered text value will be interpreted as material symbols icon.

</td>
</tr>
<tr>
<td>

**setSize**

</td>
<td>

`x: number, y: number`

</td>
<td>

Set size of display element. Max `x` value is `120px`, max `y` value is `960px`.

</td>
</tr>
<tr>
<td>

**setMargin**

</td>
<td>

`top: number | 'auto', right: number | 'auto', bottom: number | 'auto', left: number | 'auto'`

</td>
<td>

Set element margin.

</td>
</tr>
<tr>
<td>

**setBorderRadius**

</td>
<td>

`topLeft: number, topRight: number, bottomRight: number, bottomLeft: number`

</td>
<td>

Set element border radius.

</td>
</tr>
<tr>
<td>

**registerOnTouchStartHandler**

</td>
<td>

`handler: func`

</td>
<td>

Register handler, invoked when screen touch has been started. <br><br>  Definition:<br> 
```js 
function(instance IWidgetInstance) => void
```

</td>
</tr>
<tr>
<td>

**registerOnTouchEndHandler**

</td>
<td>

`handler: func`

</td>
<td>

Register handler, invoked when screen touch has been ended. <br><br> Definition:<br> 
```js
function(instance IWidgetInstance) => void
```

</td>
</tr>
<tr>
<td>

**registerOnTouchMoveHandler**

</td>
<td>

`handler: func`

</td>
<td>

Register handler, invoked when touch on the screen has been moved. <br><br>  Definition:<br> 
```js 
function(
  value: {
    deltaX: number,
    deltaY: number
  },
  instance IWidgetInstance
) => void
``` 

</td>
</tr>
</tbody>
</table>

> <br> **Instance information:** <br><br> If display text is defined `IWidgetInstance` components collection will be extended by this component. <br> <br>

### Display image - Component (DisplayImageSDK) <a id="displayImage"></a>

<table><thead>
<tr>
<th> Name </th> <th> Arguments </th> <th> Description </th>
</tr>
</thead>
<tbody>
<tr>
<td>

**setImageBase64Data**

</td>
<td>

`value: string`

</td>
<td>

Set image as base64 data string. Can be override from component object in `instance` by `set` function.

</td>
</tr>
<tr>
<td>

**setImagePath**

</td>
<td>

`value: string`

</td>
<td>

Set image as path to image. *** Function available in future ***

</td>
</tr>
<tr>
<td>

**setSize**

</td>
<td>

`x: number, y: number`

</td>
<td>

Set size of image element. Max `x` value is `120px`, max `y` value is `960px`.

</td>
</tr>
<tr>
<td>

**setBackgroundColor**

</td>
<td>

`value: string`

</td>
<td>

Set background color ```hex format ex. #111111```

</td>
</tr>
<tr>
<td>

**setMargin**

</td>
<td>

`top: number | 'auto', right: number | 'auto', bottom: number | 'auto', left: number | 'auto'`

</td>
<td>

Set element margin.

</td>
</tr>
<tr>
<td>

**setBorderRadius**

</td>
<td>

`topLeft: number, topRight: number, bottomRight: number, bottomLeft: number`

</td>
<td>

Set element border radius.

</td>
</tr>
<tr>
<td>

**registerOnTouchStartHandler**

</td>
<td>

`handler: func`

</td>
<td>

Register handler, invoked when element touch has been started <br><br>  Definition:<br>
```js
function(instance IWidgetInstance) => void
```

</td>
</tr>
<tr>
<td>

**registerOnTouchEndHandler**

</td>
<td>

`handler: func`

</td>
<td>

Register handler, invoked when element touch has been ended <br><br>  Definition:<br> 
```js
function(instance IWidgetInstance) => void
```

</td>
</tr>
<tr>
<td>

**registerOnTouchMoveHandler**

</td>
<td>

`handler: func`

</td>
<td>

Register handler, invoked when touch on the element has been moved <br><br>  Definition:<br> 
```js
function(
  value: {
    deltaX: number,
    deltaY: number
  },
  instance IWidgetInstance
) => void
```

</td>
</tr>
</tbody>
</table>

> <br> **Instance information:** <br><br>  If display image is defined `IWidgetInstance` components collection will be extended by this component. <br> <br>

### Examples

#### Basic display component - button

```js
configuration
  .registerDisplay({ name: 'exampleButtonWidget' })
  .addLayer((layer) => // create basic layer for components
    layer
      .setMargin(4, 4, 4, 4)
      .setBorderRadius(5, 5, 5, 5)
      .setBackgroundColor('#363636')
      .addColumn((column) => // create column for display component. In this case it does not matter if it is a column or a row 
        column
          .addDisplayText('icon', (text) =>
            text
              .setMargin(8, 0, 8, 0)
              .setTextAlign('center')
              .setFontSize(36)
              .setFontWeight('bold')
              .setColor('#F9F9F9')
              .setText('open_in_new')
              .setIsIcon(true), // text will be interpreted as material symbols icon
          )
          .registerOnTouchEndHandler((instance) => {
            // hey i just got clicked!
          }),
      ),
  )
```

#### Usage of display slider component

```js
configuration
  .registerDisplay({ name: 'exampleSliderWidget' })
  .setSize(2, 1)
  .addLayer((layer) =>
    layer
      .setMargin(4, 4, 4, 4)
      .setBorderRadius(5, 5, 5, 5)
      .setBackgroundColor('#363636')
      .addDisplaySlider('volumeProgress', (slider) =>
        slider
          .setSize(52, 112)
          .setColor('6f6f6f')
          .setOrientation('vertical')
          .setBackgroundColor('#363636')
          .setIcon('volume_up')
          .setIconColor('#ffffff')
          .registerOnChangeHandler((value, instance) => {
            // hey i just got changed!
          }),
      ),
  );
```

#### Usage of display image component

```js
configuration
      .registerDisplay({ name: 'cover' })
      .setSize(2, 2)
      .addLayer((layer) =>
        layer
          .setMargin(4, 4, 4, 4)
          .setBorderRadius(5, 5, 5, 5)
          .addDisplayImage('cover', (cover) =>
            cover
              .setSize(112, 112)
              .setImageBase64Data(
                'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAEAAAABCAQAAAC1HAwCAAAAC0lEQVR42mNkYAAAAAYAAjCB0C8AAAAASUVORK5CYII=',
              ),
          ),
      )
```

#### Usage of initialize and deactivate handlers with change components state

```js
configuration
      .registerDisplay({ name: 'player' })
      .setSize(2, 2)
      .registerOnInitializeHandler((instance) => {
        // when cover change event has been invoke, image in background layer can be changed by usage set function of cover component object.
        // change value rules of other components is the same as in this example. 
        const coverChangeHandler = (imageDataUri) => {
          instance.components.cover.set(imageDataUri);
        };

        // some service that manage state of player can register and invoke events
        playerService.registerOnCoverChange(instance.id, coverChangeHandler);
      })
      .registerOnDeactivateHandler((id) => {
        // unregister event
        playerService.unregisterOnCoverChange(instance.id);
      })
      .addLayer((layer) => // background layer
        layer
          .setMargin(4, 4, 4, 4)
          .setBorderRadius(5, 5, 5, 5)
          .addDisplayImage('cover', (cover) =>
            cover
              .setSize(112, 112)
              .setImageBase64Data(
                'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAEAAAABCAQAAAC1HAwCAAAAC0lEQVR42mNkYAAAAAYAAjCB0C8AAAAASUVORK5CYII=',
              ),
          ),
      )
      .addLayer((layer) => // foreground layer
        layer... // rest player
      );
```

## Widgets base API <a id="widgetsBaseAPI"></a>

| Name | Arguments | Description |
|------|-----------|-------------|
| **registerOnInitializeHandler** | `handler: func` | Register handler invoked when module has been initialized. Returns widget instance that contains set method, widget id, is active status and configuration.  <br><br>  Definition:<br> ```function(instance: IWidgetInstance) => void```|
| **registerOnDeactivateHandler** | `handler: func` | Register handler invoked when module has been deactivated. Handlers are deactivated by default. If you use external functions to get data you should remove listerners in deactivate handler. If you invoke setter on deactivated widget, sdk throws exception.  <br><br>  Definition:<br> ```function(id: string) => void```|

### Examples

#### Register on initialize handler based on slider widget

```js
configuration.registerSlider(...)
  .registerOnInitializeHandler(({ set }) => {
    // slider has been initialized!

    set(10); // set 10 as slider value when initialized
  });
```

```js
configuration.registerSlider(...)
  .registerOnInitializeHandler((instance) => {
    // slider has been initialized!

    if(instance.isActive)
    {
        instance.set(0);
    }
  });
```

#### Register on deactivate handler based on slider widget

```js

let sliderInstances = []

configuration.registerSlider(...)
  .registerOnInitializeHandler(({ id, set }) => {
    const instance = {
      id,
      set,
      handleSetSliderValue: (value) => {
        ...
      }
    };
    
    sliderInstances.push(instance)

    addEventListerner('setSliderValue', instance.handleSetSliderValue);
  })
  .registerOnDeactivateHandler((idToDeactivate) => {
    // slider has been deactivated!
    const sliderInstanceIndex = sliderInstances.find(({ id }) => id === idToDeactivate);

    removeEventListerner('setSliderValue', sliderInstance.handleSetSliderValue);

    sliderInstances = sliderInstances.filter(({ id }) => id !== idToDeactivate);
  });
```

## Widgets system API <a id="widgetsSystemAPI"></a>

| Name | Arguments | Description |
|------|-----------|-------------|
| **useSystemVolume** | `handler: func` | Register handler invoked when system value changed. When system volume is used, `setSystemVolume` setter will be available in `instance` <br><br> Definition:<br> ```function(value: number, instance IWidgetInstance) => void```  |

```ts

IWidgetInstance {
  ...
  set: (value: number) => void; // value can be number in 0-100 range
}
```

### Examples

#### Register useSystemVolume handler based on slider widget

```js

let sliderInstances = []

configuration.registerSlider(...)
  .registerOnChangeHandler((value, instance) => {
    log.info('hey, slider value is', value);

    instance.setSystemVolume(value);
  });
  .useSystemVolume((value, instance) => {
    log.info('hey, system value is', value);

    instance.set(value);
  });
```

| Name | Arguments | Description |
|------|-----------|-------------|
| **useMicrophoneSystemVolume** | `handler: func` | Register handler invoked when system microphone value changed. When system microphone volume is used, function `set`  will be available in `instance` <br><br> Definition:<br> ```function(value: number, instance IWidgetInstance) => void```  |

```ts

IWidgetInstance {
  ...
  set: (value: number) => void; // value can be number in 0-100 range
}
```

### Examples

#### Register useSystemVolume and useMicrophoneSystemVolume handler based on slider widget

```js

configuration.registerSlider(...)
  .addDropdown({
      key: 'selectedMicrophone',
      name: 'Select microphone device',
      description: 'Select the microphone to control',
      source: (instance) => {
        return getMicrophoneDevices(
         ...
        );
      },
    })
  .registerOnChangeHandler((value, instance) => {
    log.info('hey, slider value is', value);

    instance.setSystemVolume(value, 'Mike');
  });
  .useSystemVolume(() => {})
  .useMicrophoneSystemVolume((value, instance) => {
      instance.set(value);
    }, 
    'selectedMicrophone'
  );
```

| Name | Arguments | Description |
|------|-----------|-------------|
| **useMicrophoneSystemMuteState** |  Register handler invoked when system microphone state changed. When system microphone state is used, function `set` will be available in `instance` <br><br> Definition:<br> ```function(value: boolean, instance IWidgetInstance) => void```  |

### Examples

#### Register useMicrophoneSystemMuteState handler based on led widget

```js

configuration.registerLedCluster(...)
  .useMicrophoneSystemMuteState((value, instance) => {
      const array = [];

      for (let i = 0; i <= instance.numberOfLeds; i++) {
        if (!value) {
          array.push('#333333FF');
        } else {
          array.push(null);
        }
      }

      instance.set(array);
  });
```

| Name | Arguments | Description |
|------|-----------|-------------|
| **useSystemInstalledApps** | `handler: func` | Register handler invoked when system installed apps changed. <br><br> Definition:<br> ```function(apps: InstalledApps, instance IWidgetInstance) => void```  |

### Examples

#### Register useSystemInstalledApps handler based on key widget

```js

configuration.registerKey(...)
    .registerOnInitializeHandler((instance) => {
      //Get initial application list
      log.info(instance.applications);
    })
   .useSystemInstalledApps((applications, instance) => {
      //Get application list on change
      log.info(applications);
    })
```

| Name | Arguments | Description |
|------|-----------|-------------|
| **useAudioApps** | `handler: func` | Register handler invoked when system audio apps changed. <br><br> Definition:<br> ```function(availableAudioApplications: AvailableAudioApps, instance IWidgetInstance) => void```  |

### Examples

#### Register useAudioApps handler based on key widget

```js

configuration.registerKey(...)
    .registerOnInitializeHandler((instance) => {
      //Get audio application list
      log.info(instance.availableAudioApplications);
    })
   .useAudioApps((availableAudioApplications, instance) => {
      //Get audio application list on change
      log.info(availableAudioApplications);
    })
```

| Name | Arguments | Description |
|------|-----------|-------------|
| **useSystemAvailableDevices** | `handler: func` | Register handler invoked when system devices list changed. <br><br> Definition:<br> ```function(devices: AvailableDevices, instance IWidgetInstance) => void```  |

### Examples

#### Register useSystemAvailableDevices handler based on key widget

```js

configuration.registerKey(...)
    .registerOnInitializeHandler((instance) => {
      //Get speakers list
      log.info(instance.speakers);
    })
   .useSystemAvailableDevices((speakers, instance) => {
      //Get speakers list on change
      log.info(speakers);
    })
```

| Name | Arguments | Description |
|------|-----------|-------------|
| **useSystemAvailableMicrophoneDevices** | `handler: func` | Register handler invoked when system microphone device list changed. <br><br> Definition:<br> ```function(devices: AvailableDevices, instance IWidgetInstance) => void```  |

### Examples

#### Register useSystemAvailableMicrophoneDevices handler based on key widget

```js

configuration.registerKey(...)
    .registerOnInitializeHandler((instance) => {
      //Get microphone device list
      log.info(instance.microphones);
    })
   .useSystemAvailableMicrophoneDevices((microphones, instance) => {
      //Get microphone device list on change
      log.info(microphones);
    })
```

| Name | Arguments | Description |
|------|-----------|-------------|
| **useSystemMonitorResources** | `handler: func` | Register handler invoked when system resource state changed. <br><br> Definition:<br> ```function(resources: SystemMonitorResourcesPayload, instance IWidgetInstance) => void``` |

Payload structure: <br>  

```js
interface CpuResource {
  usageInPercentage: number;
  temperatureInCelsius: number;
  clockInMhz: number;
  fanSpeedInRpm: number;
}

interface GpuResource {
  usageInPercentage: number;
  temperatureInCelsius: number;
  clockInMhz: number;
  fanSpeedInRpm: number;
}

interface RamResource {
  usageInPercentage: number;
}

interface DiskResource {
  storageUsedInPercentage: number;
}

interface NetworkSpeed {
  downloadInKbs: number;
  uploadInKbs: number;
}

interface NetworkResource {
  wifi: NetworkSpeed;
  ethernet: NetworkSpeed;
}

interface Payload {
  cpu: CpuResource;
  gpu: GpuResource;
  ram: RamResource;
  disk: DiskResource;
  network: NetworkResource;
}
```

### Examples

#### Register useSystemMonitorResources handler based on led widget

```js

configuration.registerLedCluster(...)
   .useSystemMonitorResources((resource, instance) => {
      //Get CPU
      log.info(resource.cpu.usageInPercentage);
      //Get GPU usage
      log.info(resource.gpu.usageInPercentage);
      //Get RAM usage
      log.info(resource.ram.usageInPercentage);
      //Get Storage usage
      log.info(resource.disk.storageUsedInPercentage);
      //Get Network usage -  Windows
      log.info(resource.network.wifi.uploadInKbs);
      log.info(resource.network.wifi.downloadInKbs);
      log.info(resource.network.ethernet.uploadInKbs);
      log.info(resource.network.ethernet.downloadInKbs);
      //Get Network usage -  macOS
      log.info(resource.network.download);
      log.info(resource.network.upload);
    })
```

| Name | Arguments | Description |
|------|-----------|-------------|
| **useSystemMuteMicrophone** |  When system mute microphone is used, `muteMicrophone` setter will be available in `instance` <br><br> Definition:<br> ```function(deviceId: string) => void```  |

### Examples

#### Register useSystemMuteMicrophone handler based on key widget

```js

configuration.registerKey(...)
    .registerOnKeyUpHandler((instance) => {
      instance.muteMicrophone(''); //selected device or default active device
    })
   .useSystemMuteMicrophone()
```

| Name | Arguments | Description |
|------|-----------|-------------|
| **useSystemUnmuteMicrophone** |  When system unmute microphone  is used, `unmuteMicrophone` setter will be available in `instance` <br><br> Definition:<br> ```function(deviceId: string) => void```  |

### Examples

#### Register useSystemUnmuteMicrophone handler based on key widget

```js

configuration.registerKey(...)
    .registerOnKeyUpHandler((instance) => {
      instance.unmuteMicrophone(''); //selected device or default active device
    })
   .useSystemUnmuteMicrophone()
```

| Name | Arguments | Description |
|------|-----------|-------------|
| **useSystemTakeScreenshot** |  When system Screenshot is used, `takeScreenshot` setter will be available in `instance` <br><br> Definition:<br> ```function(saveLocation: string) => void```  |

### Examples

#### Register useSystemTakeScreenshot handler based on key widget

```js

configuration.registerKey(...)
     .addInput(
      {
        key: 'savePath',
        name: 'Save screenshot directory',
        description: 'Choose the path to save screenshot',
      },
      'directory',
    )
    .registerOnKeyUpHandler((instance) => {
      instance.takeScreenshot(
        path.join(
         instance.configuration.savePath,
          `Screenshot-${new Date().toISOString().replaceAll(':', '-')}.jpg`,
        ),
      );
    })
   .useSystemTakeScreenshot()
```

| Name | Arguments | Description |
|------|-----------|-------------|
| **useSystemControlSystemMediaPlayer** |  When system control media player is used, `setControlSystemMediaPlayer` setter will be available in `instance` <br><br> Definition:<br> ```function(playerAction: PlayerCommand) => void```  |

### Examples

#### Register useSystemControlSystemMediaPlayer handler based on key widget

```js

configuration.registerKey(...)
    .registerOnKeyUpHandler((instance) => {
      instance.setControlSystemMediaPlayer('play/pause');
    });
   .useSystemControlSystemMediaPlayer()
```

| Name | Arguments | Description |
|------|-----------|-------------|
| **useOpenApp** |  When system open app is used, `openApp` setter will be available in `instance` <br><br> Definition:<br> ```function(appId: string) => void```  |

### Examples

#### Register useOpenApp handler based on key widget

```js

configuration.registerKey(...)
    .registerOnKeyUpHandler((instance) => {
      instance.openApp('com.google.Chrome');
    })
   .useOpenApp()
```

| Name | Arguments | Description |
|------|-----------|-------------|
| **useKeystrokes** |  When system key strokes is used, `pressKeystrokes` setter will be available in `instance` <br><br> Definition:<br> ```function(keyCodes: number[], appId?: string) => void```  |

### Examples

#### Register useKeystrokes handler based on key widget

```js

configuration.registerKey(...)
    .addInput(
      {
        key: 'keystrokes',
        name: 'Keystrokes',
        description: 'Keystroke to run',
      },
      'keystroke',
    )
    .registerOnKeyDownHandler((instance) => {
      instance.openApp('com.google.Chrome');
      instance.pressKeystrokes(
        instance.configuration.keystrokes,
        'com.google.Chrome', //selected application to execute the keystroke or live empty to run on current active application
      );
    })
   .useKeystrokes()
```

## Widgets system WINDOWS API <a id="widgetsSystemWindowsAPI"></a>

To use the SDK for Windows, you need to put a setter that will enable you to use functions available only for this system.

### Examples

#### Register Windows SDK based on slider widget

```js

configuration.registerSlider(...)
    .useWindowsSDK(windowsSDK => 
      windowsSDK.useAppVolume(...)
    );
```

> [!WARNING]
> **useWindowsSDK** call has been changed to maintain SDK consistency. The previous implementation resulted in the inability to continue using the widget functionality due to SDK support. The Windows SDK has been backported and is available as an argument to the **useWindowsSDK** function.

| Name | Arguments | Description |
|------|-----------|-------------|
| **useAppVolume** | `handler: func` | Register handler invoked when application value changed. When app volume is used, `setAppVolume` setter will be available in `instance` <br><br> Definition:<br> ```function(applicationPropertyName: string, handler: (value: number, instance: IWidgetInstance)) => void```  |

### Examples

#### Register application volume in Windows based on slider widget

```js

configuration.registerSlider({ name: 'Slider name' }, 'win32')
    .addInput({
        key: 'selectedApp',
        name: 'Select application',
      },
      'string'
    )
    .registerOnChangeHandler((value, instance) => {
      if (instance.configuration.selectedApp) {
        instance.windows.setAppVolume(
          value,
          instance.configuration.selectedApp,
        );
      }
    })
    .useWindowsSDK((windowsSDK) => 
      windowsSDK.useAppVolume('selectedApp', (value, instance) => {
        instance.set(value);
      })
    )
```

## Instances <a id="instances"></a>

Instances allow you to store selected configuration values.

Each instance has its own id, which uniquely identifies the widget pinned to a specific plugin.

### Example

#### The selected input value based on slider widget

```js

configuration.registerSlider(...)
    .addInput({
        key: 'exampleInputValue',
        name: 'exampleInputValueName',
      },
      'string'
    )
    .registerOnInitializeHandler((instance) => {
      //Use selected value like this
      log.info(instance.configuration?.exampleInputValue);
    })
    .registerOnConfigurationChangeHandler((configurationProperty, instance) => {
      if (configurationProperty.key === 'exampleInputValue') {
        //Selected value changed
        log.info(configurationProperty.value);
      }
    })
    .registerOnChangeHandler((value, instance) => {
      //Use selected value in handler action
      log.info(instance.configuration?.exampleInputValue);
    });
```

#### The selected dropdown value based on slider widget

```js

configuration.registerSlider(...)
    .addDropdown({
      key: 'exampleDropdownValue',
      name: 'exampleName',
      description: 'exampleDescription',
      source: () => {
        return getExampleArray();
      },
    })
    .registerOnInitializeHandler((instance) => {
      //Use selected value like this
      log.info(instance.configuration?.exampleDropdownValue);
    })
    .registerOnConfigurationChangeHandler((configurationProperty, instance) => {
      if (configurationProperty.key === 'exampleDropdownValue') {
        //Selected value changed
        log.info(configurationProperty.value);
      }
    })
    .registerOnChangeHandler((value, instance) => {
      //Use selected value in handler action
      log.info(instance.configuration?.exampleDropdownValue)
    });
```

#### The selected dropdown value based on slider widget

```js

configuration.registerSlider(...)
    .addDropdown({
      key: 'exampleDropdownValue',
      name: 'exampleName',
      description: 'exampleDescription',
      source: () => {
        return getExampleArray();
      },
    })
    .registerOnInitializeHandler((instance) => {
      //Use selected value like this
      log.info(instance.configuration?.exampleDropdownValue);
    })
    .registerOnConfigurationChangeHandler((configurationProperty, instance) => {
      if (configurationProperty.key === 'exampleDropdownValue') {
        //Selected value changed
        log.info(configurationProperty.value);
      }
    })
    .registerOnChangeHandler((value, instance) => {
      //Use selected value in handler action
      log.info(instance.configuration?.exampleDropdownValue)
    });
```

#### Working with instance id based on slider widget

```js

const localValue = = {};

configuration.registerSlider(...)
    .addInput({
        key: 'exampleInputValue',
        name: 'exampleInputValueName',
      },
      'number'
    )
    .registerOnConfigurationChangeHandler((configurationProperty, instance) => {
      if (configurationProperty.key === 'exampleInputValue') {
        localValue[instance.id] = configurationProperty.value;
      }
    })
    .registerOnChangeHandler((value, instance) => {
      const currentValue = localValue[instance.id];
      let newValue = currentValue + value;

      localValue[instance.id] = newValue;
    });
```

## Widgets configuration API <a id="widgetsConfigurationAPI"></a>

```ts
interface ISourceElement {
  label: string;
  value: string;
}
```

<table>
<thead>

<tr>
<th> Name </th> <th> Arguments </th> <th> Description </th>
</tr>
</thead>
<tbody>
<tr>
<td>

**addDropdown**

</td>
<td>

`dropdownConfiguration: Object, options: Object`

</td>
<td>

Add dropdown configuration property with options to select or function which return options to select.

Definition:

```js
dropdownConfiguration: {
    key: string;
    name: string;
    description: string;
    source: () => ISourceElement[]
      | ISourceElement[];
    dependencies?: string[]; // keys of another controls that depends. If configuration of controls changed, source will be invoked.
}

options: {
  required?: boolean;
}
```

</td>
</tr>
<tr>
<td>

**addInput**

</td>
<td>

`inputConfiguration: Object, inputType: string, options: Object`

</td>
<td>

Add input configuration property

Definition:

```js
inputConfiguration: {
    key: string;
    name: string;
    description: string;
}

inputType: 'string' | 'number' | 'directory' | 'keystroke'

options: {
  min?: number;
  max?: number;
  required?: boolean;
}
```

</td>
</tr>
<tr>
<td>

**addArray**

</td>
<td>

`arrayConfiguration: Object, fieldsConfiguration: Object`

</td>
<td>

Add array configuration property

Definition:

```js
arrayConfiguration: {
    key: string,
    name: string,
}
fieldsConfiguration: array of Widget configuration API (configurationSDK)
```

</td>
</tr>
<tr>
<td>

**addReadonly**

</td>
<td>

`inputConfiguration: Object`

</td>
<td>

Add readonly configuration property

Definition:

```js
{
    key: string,
    name: string,
    description: string
}
```

</td>
</tr>
<tr>
<td>

**registerOnConfigurationChangeHandler**

</td>
<td>

`handler: func`  

</td>
<td>

Add readonly configuration property

Definition:

```js
handler: function({
  key: string,
  value: any
}) => void,
```

</td>
</tr>
</tbody>

</table>

### Examples

#### Register dropdown configuration property based on slider widget

```js
configuration.registerSlider(...)
  .addDropdown({
    key: 'exampleConfigurationKey',
    name: 'Visible name in UI configuration',
    description: 'Visible description in UI Configuration',
    source: [{
      label: 'Option1'
      value: 'key1',
    }, {
      label: 'Option2'
      value: 'key2',
    }]
  });

```

Instead of source array you can use function that returns array of source elements:

```js
configuration.registerSlider(...)
  .addDropdown({
    ...
    source: () => {
      // some logic to get array of parameters

      return [{
        label: 'Option1'
        value: 'key1',
      }, {
        label: 'Option2'
        value: 'key2',
      }];
    }
  });
```

#### Register readonly configuration property based on slider widget

```js
configuration.registerSlider(...)
  .addReadonly({
    key: 'exampleConfigurationKey',
    name: 'Visible name in UI configuration',
    description: 'Visible description in UI Configuration',
  });

```

#### Register array configuration property based on key widget

```js
configuration.registerKey(...)
  .addArray(
    {
    key: 'exampleConfigurationKey',
    name: 'Visible name in UI configuration',
    },
    (arrayConfiguration) =>
        arrayConfiguration
          .addDropdown({
            key: 'exampleDropdownKey',
            name: 'exampleDropdownName',
            description: 'exampleDropdownDescription',
            source: () => {
              return GetList();
            },
          })
          .addDropdown({
            key: 'exampleDropdownKey1',
            name: 'exampleDropdownName1',
            description: 'exampleDropdownDescription2',
            source: () => {
              return GetOtherList();
            },
          })
          .addInput({
            key: 'exampleInputKey',
            name: 'exampleInputName',
            description: 'exampleInputDescription',
            },
            'number',
            {
              min: 0,
              max: 127,
              required: true,
            },
          ),
        );

```

#### Register configuration change handler based on slider widget

```js
configuration.registerSlider(...)
  .addDropdown({
    key: 'exampleConfigurationKey',
    ...
    source: [{
      label: 'testLabel',
      value: 'testValue'
    }]
  })
  .registerOnConfigurationChangeHandler((configurationProperty) => { // invokes when user select value in dropdown
      configurationProperty.key // exampleConfigurationKey
      configurationProperty.value // maybe 'testValue'
  })
```

## Widgets events <a id="widgetsEvents"></a>

<table>
<thead>

<tr>
<th> Name </th> <th> Arguments </th> <th> Description </th>
</tr>
</thead>
<tbody>
<tr>
<td>

**registerEventHandler**

</td>
<td>

`name: string, handler: func`

</td>
<td>

Register event handler that can be invoked from other widgets in the same plugin. Handler can be invoked by **instance.sendWidget** function (check example)

Definition:

```js
handler: function(value: unknown, instance: IWidgetInstance) => void,
```

</td>
</tr>

</tbody>

</table>

### Examples

```js
configuration
    .registerKey({ name: 'invoker' })
    .registerOnKeyDownHandler((instance) => {
      instance.sendEvent('setSliderValue', 1);
    })
    .registerOnKeyUpHandler((instance) => {
      instance.sendEvent('setSliderValue', 100);
    })

  configuration
    .registerSlider({ name: 'handler' })
    .registerEventHandler('setSliderValue', (value, instance) => {
      console.log('handle event', value);

      instance.set(value);
    })
```

## Plugin configuration API <a id="pluginConfigurationAPI"></a>

<table>
<thead>

<tr>
<th> Name </th> <th> Arguments </th> <th> Description </th>
</tr>
</thead>
<tbody>
<tr>
<td>

**useConfiguration**

</td>
<td>

</td>
<td>

Plugin configuration api will be available when `useConfiguration` has been used (check examples).

</td>
</tr>
<tr>
<td>

**useInternalAuthorizationHandler**

</td>
<td>

`handler: func, action: string`

</td>
<td>

modue app can handle authorization or other request by modue protocol. All redirections should be done with **`modue://{pluginName}/{action}?{queryParameters}`** address. All **`@`** will be deleted and all **`/`** signs will be replaced by **`-`**. Action parameter is not required, then redirection should be done with **`modue://{pluginName}?{queryParameters`}**. Query parameters will be parse to object.

Definition:

```js
handler: function(query: { [key: string]: string }, action?: string) => void,
```

</td>
</tr>
<tr>
<td>

**addReadonly**

</td>
<td>

`inputConfiguration: Object`

</td>
<td>

Add readonly configuration property

Definition:

```js
{
    key: string,
    name: string,
    description: string
}
```

</td>
</tr>
<tr>
<td>

**addButton**

</td>
<td>

`buttonConfiguration: Object`

</td>
<td>

Add button configuration property. Can be used to invoke some function that change configuration.

Definition:

```js
{
    key: string,
    name: string,
    description: string,
    handler: async () => void,
    renderer: string | (() => string)
}
```

</td>
</tr>
<tr>
<td>

**addInput**

</td>
<td>

`inputConfiguration: Object, inputType: string, options: Object`

</td>
<td>

Add input configuration property

Definition:

```js
inputConfiguration: {
    key: string;
    name: string;
    description: string;
}

inputType: 'string' | 'number' | 'directory' | 'keystroke' | 'password'

options: {
  min?: number;
  max?: number;
  required?: boolean;
}
```

</td>
</tr>
<tr>
<td>

**addSwitch**

</td>
<td>

`switchConfiguration: Object, options: Object`

</td>
<td>

Add switch configuration property

Definition:

```js
switchConfiguration: {
    key: string;
    name: string;
    description: string;
}

options: {
  required?: boolean;
}
```

</td>
</tr>

</tbody>

</table>

### Examples

#### Use internal authorization handler

```js
// modue://{pluginName}?token=123

configuration
  .useConfiguration()
  .useInternalAuthorizationHandler((parms) => { // { token: "123" }
    // Invoked authorization handler with query params
  })
```

#### Use internal authorization handler with action parameter

```js
// modue://{pluginName}/myTestAction?token=123

configuration
  .useConfiguration()
  .useInternalAuthorizationHandler(...) // not invoked
  .useInternalAuthorizationHandler((parms) => { // { token: "123" }
    // Invoked authorization handler with query params
  }, 'myTestAction')
```

#### Register button in configuration based on slider widget

```js
configuration
  .useConfiguration()
  .addButton({
    key: 'testButton',
    name: 'Test button',
    renderer: 'Test button text',
    description: 'Test button description',
    handler: async () => {
      // invoke some action ex. external authorization
    },
  })
```

#### Register input in configuration to choose some directory path

```js
configuration
  .useConfiguration()
  .addInput({
    key: 'testDirectoryPath',
    name: 'Test input',
    description: 'Test input description'
  },
  'directory'
  )
```

#### Register input type password in configuration

```js
configuration
  .useConfiguration()
  .addInput({
    key: 'testDirectoryPath',
    name: 'Test input',
    description: 'Test input description'
  },
  'password'
  )
```

## Plugin storage API <a id="pluginStorageAPI"></a>

Plugin storage should be use to store only configuration data. Application can use storage to show configuration properties in plugin settings. Displaying a parameter will depend on the compatibility of the parameter names.

<table>
<thead>

<tr>
<th> Name </th> <th> Arguments </th> <th> Description </th>
</tr>
</thead>
<tbody>
<tr>
<td>

**get**

</td>
<td>

`propertyName: string`

</td>
<td>

Get data by property name from plugin configuraiton.

</td>
</tr>
<tr>
<td>

**set**

</td>
<td>

`propertyName: string, data: unknown`

</td>
<td>

Set data by property name in plugin configuration

</td>
</tr>
<tr>
<td>

**remove**

</td>
<td>

`propertyName: string`

</td>
<td>

Remove data by property name from configuration

</td>
</tr>
</tbody>

</table>

### Examples

#### Use storage functions

```js
export default (configuration, storage) => {
  const value = '123';
  const propertyName = 'propertyTest';

  storage.set(propertyName, value);

  const valueFromStorage = storage.get(propertyName); // '123'

  storage.remove(propertyName);

  const emptyValueFromStorage = storage.get(propertyName); // undefined
};

```

## Internationalization i18n - transaltions <a id="translations"></a>

<table>
<thead>

<tr>
<th> Name </th> <th> Arguments </th> <th> Description </th>
</tr>
</thead>
<tbody>
<tr>
<td>

**registerI18n**

</td>
<td>

`i18n: Object`

</td>
<td>

Register translations in the plugin. Translations will be used to replace configration keys ex. in my plugins view or selected brick configuration. When translation will be not found the value to display will be the key value.

Definition:

```js
{
    [languageCode: string]: {
      [key: string]: string
    },
}
```

</td>
</tr>
</tbody>

</table>

### Supported languages

```
enum SUPPORTED_LANGUAGES {
  PL = 'pl',
  EN = 'en',
}
```

### Examples

#### Use i18n object to translate UI

```js
configuration.
  .registerI18n({
    pl: {
      hello: 'Witaj',
      world: 'Świecie',
    },
    en: {
      hello: 'Hello',
      world: 'World'
    }
  });

```

## DevTools Log <a id="devToolsLog"></a>

Plugin log can be used to print infomation in a dev tools console - available in menu after enabling developer mode.

<table>
<thead>

<tr>
<th> Name </th> <th> Arguments </th> <th> Description </th>
</tr>
</thead>
<tbody>
<tr>
<td>

**error**

</td>
<td>

`message: string`

</td>
<td>

Log error message

</td>
</tr>
<tr>
<td>

**warn**

</td>
<td>

`message: string,`

</td>
<td>

Log warning message

</td>
</tr>
<tr>
<td>

**info**

</td>
<td>

`message: string`

</td>
<td>

Log info message

</td>
</tr>
</tbody>

</table>

### Examples

#### Use storage functions

```js
export default (configuration, storage, log) => {
  log.info('This is my message for you!');
};

```

## DevTools Log <a id="messages"></a>

Messages can be used to print infomation in modal component.

<table>
<thead>

<tr>
<th> Name </th> <th> Arguments </th> <th> Description </th>
</tr>
</thead>
<tbody>
<tr>
<td>

**useMessages**

</td>
<td>

</td>
<td>

Plugin messages api will be available when `useMessages` has been used (check examples).

</td>
</tr>
<tr>
<td>

**showMessage**

</td>
<td>

`message: Object`

</td>
<td>

Use to show message in modue UI. Fields `message` and `title` can be type of `string`. Other types are not valid and will be ommited. Fields title, message and name parameter from actions array are translated. To translate use the same key as in the supported language file (check example).

Definition:

```js
{
  title: string,
  message: string,
  disableCancelAction?: boolean,
  actions: [
    {
      name: string,
      handler: async () => void
    },
  ],
}
```

</td>
</tr>

</tbody>

</table>

### Examples

#### Show message in modue UI

```js
 configuration
  .useMessages()
  .showMessage({
    title: 'Title',
    message: 'My message to modue UI user.', 
    disableCancelAction: true, // if not defined or false cancel button will be default visible
    actions: [
      {
        name: 'Agree',
        handler: () => {
          log.info('handled');
        },
      },
    ],
  });
```

#### Use show message with translations

```js
configuration.
  .registerI18n({
    pl: {
      title: 'Wiadomość',
      message: 'Mój pierwszy komunikat do modue UI!',
      ok: 'Ok',
    },
    en: {
      title: 'Message',
      message: 'My first message to modue UI!',
      ok: 'Ok',
    }
  });

configuration
  .useMessages()
  .showMessage({
    title: 'title',
    message: 'message', 
    disableCancelAction: true, // if not defined or false cancel button will be default visible
    actions: [
      {
        name: 'ok',
        handler: () => {
          log.info('handled');
        },
      },
    ],
  });
```

## Changelog <a id="changelog"></a>

You can add a file with the change history to the plugin.

The file must be named "CHANGELOG.md" and must be at the lowest level (the same level as the package.json file)

### Changelog structure

The description of changes for a specific version should be placed under the tag of this version in the form \*\*version number\*\* and above the tag of the previous version. In order to correctly display changes for the first version, it is suggested to add a version tag in the form \*\*0.0.0\*\* at the end of its description

```md
# Changelog title
Title

**1.1.1**
no changhes at all.

**1.1.0**
## CHANGEEEES!

Version is downloaded from `${package.json.version}`.

> Note: `some note` is note.

The port is

127.0.0.1:8000

Another changes

**1.0.1**

- Make some extreme changes
- Plugin is slower

**1.0.0**

- Initial release

**0.0.0**
```
