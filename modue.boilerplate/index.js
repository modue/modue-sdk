const imageBase64 =
  'data:image/jpeg;base64,/9j/4AAQSkZJRgABAQAAAQABAAD/2wBDAAMCAgMCAgMDAwMEAwMEBQgFBQQEBQoHBwYIDAoMDAsKCwsNDhIQDQ4RDgsLEBYQERMUFRUVDA8XGBYUGBIUFRT/wgALCADIAMgBAREA/8QAFgABAQEAAAAAAAAAAAAAAAAAAAgH/9oACAEBAAAAAcMAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAaPo4BnGcAAKOo4AnGcQAFHUcATjOIACjqOAJxnEABR1HAE4ziAAo6jgCcZxAAUdRwBOM4gAKOo4AnGcQAFHUdm+c6Po+b5zo+jzjOIACjqOnGcaOo6cZxo6jpxnEABo+j5xnGj6PnGcaPo+cZwAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA//EABsQAAEFAQEAAAAAAAAAAAAAAAYABxYXMBBw/9oACAEBAAEFAvNg8Plap9U+qfVPqn1T6p9U+qfRgHxTdn8ng3Z/J4N2fyeDdn8ng3Z/J4N2fyeDdn8ng3Z/hgYRRXAg8wlfDAwiiuBB5hK+PBuz/Hg4z/Hg4z/Hg3DzCKK4EYGEr4HmEUVwIwMJXwPMIorgRgYSvzf/xAAnEAAAAQkJAQAAAAAAAAAAAAARAAUSMDWDpMLiAQQQExQkQ1FhcP/aAAgBAQAGPwL5te93pchHjTER9s6JrQ1RNaGqJrQ1RNaGqJrQ1RNaGqJrQ1RNaGqJrQ1RXTd6rPS40AAPbe152dTqjS9kXnZ1OqNL2RednU6o0vZF52dTqjS9kXnZ1OqNL2RednU6o0vZF52dTqjS9kXnZ1PhdNpqs9LkQAA8t7JkxNJXvaaXIR5ExEfLOsLptNVnpciAAHlvZMmJpK97TS5CPImIj5Z1gaXsi87Op8DS9kwOzqfA0vZMDs6nwNL2Rfe9pqs9HkQAB8t7JkxNJXTaaXIS5ExEPLOsL3tNVno8iAAPlvZMmJpK6bTS5CXImIh5Z1he9pqs9HkQAB8t7JkxNJXTaaXIS5ExEPLOvm//xAAcEAACAwADAQAAAAAAAAAAAAARsRBh8DBBcFD/2gAIAQEAAT8h82xXegPxbu7u7u4jvYV9A7u7u7u7u7uJw79xWN1negPBOHfuKxus70B/ld3d3diO9xWNxHegPGI73FY3Ed6A8YjvcVjcR3oD+b//2gAIAQEAAAAQ/wD/AP8A/wD/AP8A/wD/AP8A/wD/AP8A/wD/AP8A/wD/AP8A/wD/AP8A/wD8AH//AP8Av/8A/wDf/wD/AO//AP8A9/8A/wD7/wD/AP3/AP8A/v8A/wCZf/8Au7//ABEf/wD/AP8A/wD/AP8A/wD/AP8A/wD/AP8A/wD/AP8A/wD/AP8A/wD/AP8A/wD/AP/EACQQAAECBQQCAwAAAAAAAAAAABEAMQEhQFHwECCBwUFwMNHh/9oACAEBAAE/EPW0fNzfcDYJkqSpKkqSpKkqSpK4+m/IC4yqDdUk3VJN1STdUk3VJN1STdQk47XxMcAXGSGJHFJbw0PJsE1Ha+JjgC4yQxI4pLeGh5NgmnUJN2wm7YTd85Pb5mOALjoJGVN3A2CaPb5mOALjoJGVN3A2CaPb5mOALjoJGVN3A2Cfrb//2Q==';

const boilerPlatePlugin = (configuration, storage, log) => {
  /** ************************************************************** */
  /** **************** Simple change event example ****************  */
  /** ************************************************************** */

  configuration
    .registerSlider({ name: 'Basic - slider change event' })
    .registerOnInitializeHandler((instance) => {
      log.info(
        `Instance with id:${instance.id} has been initialized with configuration:${JSON.stringify(instance.configuration)}`,
      );
    })
    .registerOnChangeHandler((value, instance) => {
      log.info(
        `Instance with id:${instance.id} has change slider value:${value}`,
      );
    })
    .registerOnDeactivateHandler((id) => {
      log.info(`Instance with id:${id} has been deactivated`);
    });

  configuration
    .registerKey({ name: 'Basic - key change event' })
    .registerOnInitializeHandler((instance) => {
      log.info(
        `Instance with id:${instance.id} has been initialized with configuration:${JSON.stringify(instance.configuration)}`,
      );
    })
    .registerOnKeyDownHandler((instance) => {
      log.info(`Instance with id:${instance.id} has key down event`);
    })
    .registerOnDeactivateHandler((id) => {
      log.info(`Instance with id:${id} has been deactivated`);
    });

  configuration
    .registerKnob({ name: 'Basic - knob change event' })
    .registerOnInitializeHandler((instance) => {
      log.info(
        `Instance with id:${instance.id} has been initialized with configuration:${JSON.stringify(instance.configuration)}`,
      );
    })
    .registerOnChangeHandler((value, instance) => {
      log.info(
        `Instance with id:${instance.id} has change knob value:${value}`,
      );
    })
    .registerOnDeactivateHandler((id) => {
      log.info(`Instance with id:${id} has been deactivated`);
    });

  configuration
    .registerSwitch({ name: 'Basic - switch change event' })
    .registerOnInitializeHandler((instance) => {
      log.info(
        `Instance with id:${instance.id} has been initialized with configuration:${JSON.stringify(instance.configuration)}`,
      );
    })
    .registerOnChangeHandler((value, instance) => {
      log.info(
        `Instance with id:${instance.id} has change switch value:${value}`,
      );
    })
    .registerOnDeactivateHandler((id) => {
      log.info(`Instance with id:${id} has been deactivated`);
    });

  configuration
    .registerLedCluster({ name: 'Basic - led init event' })
    .registerOnInitializeHandler((instance) => {
      log.info(
        `Instance with id:${instance.id} has been initialized with configuration:${JSON.stringify(instance.configuration)}`,
      );
      const green = '#31e000FF';
      const yellow = '#e0d100FF';
      const red = '#FF0000FF';

      const ledsToFlash = Array.from(Array(instance.numberOfLeds)).map(
        (_, index) => {
          const percentage = index / instance.numberOfLeds;

          if (percentage <= 0.5) {
            return green;
          }
          if (percentage <= 0.8) {
            return yellow;
          }
          return red;
        },
      );

      instance.set(ledsToFlash);
      log.info(
        `Instance with id:${instance.id} has flit the following LEDs: ${JSON.stringify(ledsToFlash)}`,
      );
    })
    .registerOnDeactivateHandler((id) => {
      log.info(`Instance with id:${id} has been deactivated`);
    });

  /** ************************************************************** */
  /** *************** Inputs, dropdowns and settings **************  */
  /** ************************************************************** */

  configuration
    .registerKey({ name: 'Basic - configuration & settings' }) // Register key action with name 'Basic - configuration & settings'
    .addInput(
      {
        key: 'config1',
        name: 'Example string value',
      },
      'string',
    )
    .addInput(
      {
        key: 'config2',
        name: 'Example number value',
      },
      'number',
      {
        min: 10,
        max: 60,
        required: true,
      },
    )
    .addInput(
      {
        key: 'config3',
        name: 'Example directory',
        description: 'Choose directory',
      },
      'directory',
    )
    .addInput(
      {
        key: 'config4',
        name: 'Example keys',
        description: 'Choose keystroke',
      },
      'keystroke',
    )
    .addDropdown({
      key: 'config5',
      name: 'Select option',
      description: 'Select option from list',
      source: () => {
        return [
          { label: 'Value 1', value: 1 },
          { label: 'Value 2', value: 2 },
          { label: 'Value 3', value: 3 },
        ];
      },
    })
    .registerOnInitializeHandler((instance) => {
      log.info(
        `Instance with id:${instance.id} has been initialized with configuration:${JSON.stringify(instance.configuration)}`,
      );
    })
    .registerOnConfigurationChangeHandler((configurationProperty, instance) => {
      log.info(
        `Instance with id:${instance.id} has configuration change for property ${configurationProperty.key} with value ${JSON.stringify(configurationProperty.value)}`,
      );
    })
    .registerOnKeyDownHandler((instance) => {
      log.info(`Instance with id:${instance.id} has key down event`);
    })
    .registerOnDeactivateHandler((id) => {
      log.info(`Instance with id:${id} has been deactivated`);
    });

  configuration
    .registerKey({ name: 'Basic - dropdown dependency' }) // Register key action with name 'Basic - dropdown dependency'
    .addDropdown({
      key: 'level1selection',
      name: 'Select option',
      description: 'Select option from list',
      source: () => {
        return [
          { label: 'Fruits', value: 'Fruits' },
          { label: 'Vegetables', value: 'Vegetables' },
        ];
      },
    })
    .addDropdown({
      key: 'level2selection',
      name: 'Select option',
      description: 'Select option base on first selection',
      dependencies: ['level1selection'],
      source: async (instance) => {
        if (!instance.configuration.level1selection) {
          return [];
        }

        switch (instance.configuration.level1selection) {
          case 'Fruits':
            return [
              { label: 'Apple', value: 'apple' },
              { label: 'Pear', value: 'pear' },
              { label: 'Orange', value: 'orange' },
            ];
          case 'Vegetables':
            return [
              { label: 'Cucumber', value: 'cucumber' },
              { label: 'Tomato', value: 'tomato' },
            ];
          default:
            return [];
        }
      },
    })
    .registerOnInitializeHandler((instance) => {
      log.info(
        `Instance with id:${instance.id} has been initialized with configuration:${JSON.stringify(instance.configuration)}`,
      );
    })
    .registerOnConfigurationChangeHandler((configurationProperty, instance) => {
      log.info(
        `Instance with id:${instance.id} has configuration change for property ${configurationProperty.key} with value ${JSON.stringify(configurationProperty.value)}`,
      );
    })
    .registerOnKeyDownHandler((instance) => {
      log.info(`Instance with id:${instance.id} has key down event`);
    })
    .registerOnDeactivateHandler((id) => {
      log.info(`Instance with id:${id} has been deactivated`);
    });

  /** ************************************************************** */
  /** ************** Popup messages & events example **************  */
  /** ************************************************************** */

  configuration.registerI18n({
    pl: {
      title: 'Wiadomość',
      message: 'Komunikat do modue UI',
      ok: 'Ok',
      slider: 'Suwak',
      image1x1: 'Obraz 1x1',
      rowsAndColumns: 'Wiersze oraz kolumny',
      events: 'Zdarzenia',
      image2x2: 'Obraz 2x2',
    },
    en: {
      title: 'Message',
      message: 'Message to modue UI!',
      ok: 'Ok',
      slider: 'Slider',
      image1x1: 'Image 1x1',
      rowsAndColumns: 'Rows and columns',
      events: 'Events',
      image2x2: 'Image 2x2',
    },
  });

  configuration
    .registerKey({ name: 'Basic - message event' })
    .registerOnInitializeHandler((instance) => {
      log.info(
        `Instance with id:${instance.id} has been initialized with configuration:${JSON.stringify(instance.configuration)}`,
      );
    })
    .registerOnKeyDownHandler((instance) => {
      log.info(`Instance with id:${instance.id} has key down event`);
      configuration.useMessages().showMessage({
        title: 'title',
        message: 'message',
        disableCancelAction: true, // if not defined or false cancel button will be default visible
        actions: [
          {
            name: 'ok',
            handler: () => {
              log.info('handled ok action');
            },
          },
        ],
      });
    })
    .registerOnDeactivateHandler((id) => {
      log.info(`Instance with id:${id} has been deactivated`);
    });

  /** ************************************************************** */
  /** ******************** Global, configuration ******************  */
  /** ************************************************************** */

  configuration
    .useConfiguration()
    .addButton({
      key: 'configurationButton',
      name: 'Configuration button',
      renderer: () =>
        storage.get('exampleToken') ? 'Connected' : 'Try to connect',
      description: 'Example configuration button description',
      handler: async () => {
        // invoke some action ex. external authorization
        log.info('Action has been invoked');

        log.info(`Example token if saved: ${storage.get('exampleToken')}`);
      },
    })
    .useInternalAuthorizationHandler((parms) => {
      // modue://@modue/boilerplate?token=123
      log.info(`Action has been invoked with params:${JSON.stringify(parms)}`);
      if (parms?.token) {
        storage.set('exampleToken', parms?.token);
        log.info('Save token in storage');
      }
    });

  /** ************************************************************** */
  /** ***************** System apps & devices list ****************  */
  /** ************************************************************** */

  configuration
    .registerKey({ name: 'System - installed apps' })
    .addDropdown({
      key: 'installedApplications',
      name: 'Select installed application',
      source: (instance) => {
        log.info('TUTAJ2');
        log.info(JSON.stringify(instance));
        return (
          instance.applications?.map((app) => ({
            value: app.id,
            label: app.name,
          })) || []
        );
      },
    })
    .useSystemInstalledApps((apps, instance) => {
      log.info(
        `Instance with id:${instance.id} has  updated installed application list: ${JSON.stringify(apps)}`,
      );
    })
    .registerOnInitializeHandler((instance) => {
      log.info(
        `Instance with id:${instance.id} has been initialized with configuration:${JSON.stringify(instance.configuration)}`,
      );
    })
    .registerOnConfigurationChangeHandler((configurationProperty, instance) => {
      log.info(
        `Instance with id:${instance.id} has configuration change for property ${configurationProperty.key} with value ${JSON.stringify(configurationProperty.value)}`,
      );
    })
    .registerOnDeactivateHandler((id) => {
      log.info(`Instance with id:${id} has been deactivated`);
    });

  configuration
    .registerKey({ name: 'System - audio apps' })
    .addDropdown({
      key: 'audioApplication',
      name: 'Select audio application',
      source: (instance) => {
        log.info('TUTAJ');
        log.info(JSON.stringify(instance));
        return (
          instance.availableAudioApplications?.map((app) => ({
            value: app.id,
            label: app.name,
          })) || []
        );
      },
    })
    .useAudioApps((audioAvailableApps, instance) => {
      log.info(
        `Instance with id:${instance.id} has  updated audio application list: ${JSON.stringify(audioAvailableApps)}`,
      );
    })
    .registerOnInitializeHandler((instance) => {
      log.info(
        `Instance with id:${instance.id} has been initialized with configuration:${JSON.stringify(instance.configuration)}`,
      );
    })
    .registerOnConfigurationChangeHandler((configurationProperty, instance) => {
      log.info(
        `Instance with id:${instance.id} has configuration change for property ${configurationProperty.key} with value ${JSON.stringify(configurationProperty.value)}`,
      );
    })
    .registerOnDeactivateHandler((id) => {
      log.info(`Instance with id:${id} has been deactivated`);
    });

  configuration
    .registerKey({ name: 'System - available microphone devices' })
    .addDropdown({
      key: 'microphoneDevice',
      name: 'Select microphone',
      source: (instance) => {
        return (
          instance.microphones?.map((device) => ({
            value: device.id,
            label: device.name,
          })) || []
        );
      },
    })
    .useSystemAvailableMicrophoneDevices((microphones, instance) => {
      log.info(
        `Instance with id:${instance.id} has  updated audio application list: ${JSON.stringify(microphones)}`,
      );
    })
    .registerOnInitializeHandler((instance) => {
      log.info(
        `Instance with id:${instance.id} has been initialized with configuration:${JSON.stringify(instance.configuration)}`,
      );
    })
    .registerOnConfigurationChangeHandler((configurationProperty, instance) => {
      log.info(
        `Instance with id:${instance.id} has configuration change for property ${configurationProperty.key} with value ${JSON.stringify(configurationProperty.value)}`,
      );
    })
    .registerOnDeactivateHandler((id) => {
      log.info(`Instance with id:${id} has been deactivated`);
    });

  configuration
    .registerKey({ name: 'System - available speakers' })
    .addDropdown({
      key: 'speakerDevices',
      name: 'Select speaker',
      source: (instance) => {
        return (
          instance.speakers.map((device) => ({
            value: device.id,
            label: device.name,
          })) || []
        );
      },
    })
    .useSystemAvailableMicrophoneDevices((speakers, instance) => {
      log.info(
        `Instance with id:${instance.id} has  updated audio application list: ${JSON.stringify(speakers)}`,
      );
    })
    .registerOnInitializeHandler((instance) => {
      log.info(
        `Instance with id:${instance.id} has been initialized with configuration:${JSON.stringify(instance.configuration)}`,
      );
    })
    .registerOnConfigurationChangeHandler((configurationProperty, instance) => {
      log.info(
        `Instance with id:${instance.id} has configuration change for property ${configurationProperty.key} with value ${JSON.stringify(configurationProperty.value)}`,
      );
    })
    .registerOnDeactivateHandler((id) => {
      log.info(`Instance with id:${id} has been deactivated`);
    });

  /** ************************************************************** */
  /** ************************ System volume **********************  */
  /** ************************************************************** */

  configuration
    .registerSlider({ name: 'System API - speaker volume' })
    .registerOnInitializeHandler((instance) => {
      log.info(
        `Instance with id:${instance.id} has been initialized with configuration:${JSON.stringify(instance.configuration)}`,
      );
    })
    .registerOnChangeHandler((value, instance) => {
      log.info(
        `Instance with id:${instance.id} has changed system speaker volume to ${value}`,
      );
      instance.setSystemVolume(value, 'Speakers');
    })
    .useSystemVolume((value, instance) => {
      log.info(
        `Instance with id:${instance.id} has handle system speaker volume change to ${value}`,
      );
      instance.set(value);
    })
    .registerOnDeactivateHandler((id) => {
      log.info(`Instance with id:${id} has been deactivated`);
    });

  /** ************************************************************** */
  /** ********************** System microphone ********************  */
  /** ************************************************************** */

  const lastInstanceMicrophoneState = {};
  configuration
    .registerKey({ name: 'System API - microphone mute/unmute' })
    .registerOnInitializeHandler((instance) => {
      log.info(
        `Instance with id:${instance.id} has been initialized with configuration:${JSON.stringify(instance.configuration)}`,
      );
      lastInstanceMicrophoneState[instance.id] = true;
    })
    .registerOnKeyUpHandler((instance) => {
      if (lastInstanceMicrophoneState[instance.id]) {
        log.info(`Instance with id:${instance.id} has set mute to microphone`);
        instance.muteMicrophone('');
      } else {
        log.info(
          `Instance with id:${instance.id} has set unmute to microphone`,
        );
        instance.unmuteMicrophone('');
      }
      lastInstanceMicrophoneState[instance.id] =
        !lastInstanceMicrophoneState[instance.id];
    })
    .useSystemMuteMicrophone()
    .useSystemUnmuteMicrophone()
    .registerOnDeactivateHandler((id) => {
      log.info(`Instance with id:${id} has been deactivated`);
    });

  configuration
    .registerSlider({ name: 'System API - microphone volume' })
    .registerOnInitializeHandler((instance) => {
      log.info(
        `Instance with id:${instance.id} has been initialized with configuration:${JSON.stringify(instance.configuration)}`,
      );
    })
    .registerOnChangeHandler((value, instance) => {
      log.info(
        `Instance with id:${instance.id} has set microphone volume to ${value}`,
      );
      instance.setSystemVolume(value, 'Mike'); // Set the volume of the default microphone device
    })
    .useSystemVolume(() => { })
    .useMicrophoneSystemVolume((value, instance) => {
      log.info(
        `Instance with id:${instance.id} has handle system microphone volume change to ${value}`,
      );
      instance.set(value);
    }, 'selectedMicrophone') // Register device change event action
    .registerOnDeactivateHandler((id) => {
      log.info(`Instance with id:${id} has been deactivated`);
    });

  /** ************************************************************** */
  /** ********************** System resources *********************  */
  /** ************************************************************** */

  configuration
    .registerKey({ name: 'System API - resources' })
    .registerOnInitializeHandler((instance) => {
      log.info(
        `Instance with id:${instance.id} has been initialized with configuration:${JSON.stringify(instance.configuration)}`,
      );
    })
    .useSystemMonitorResources((resource, instance) => {
      log.info(
        `Instance with id: ${instance.id} has new resources change: ${JSON.stringify(resource)}`,
      );
    })
    .registerOnDeactivateHandler((id) => {
      log.info(`Instance with id:${id} has been deactivated`);
    });

  /** ************************************************************** */
  /** *********************** Take screanshot *********************  */
  /** ************************************************************** */

  configuration
    .registerKey({ name: 'System API - screenshot' })
    .registerOnInitializeHandler((instance) => {
      log.info(
        `Instance with id:${instance.id} has been initialized with configuration:${JSON.stringify(instance.configuration)}`,
      );
    })
    .useSystemTakeScreenshot()
    .registerOnKeyUpHandler((instance) => {
      const fileName = `screenshot${Math.floor(Math.random() * 1000) + 1}.jpg`;
      log.info(
        `Instance with id:${instance.id} has saved screenshot as ${fileName}`,
      );
      instance.takeScreenshot(fileName);
    })
    .registerOnDeactivateHandler((id) => {
      log.info(`Instance with id:${id} has been deactivated`);
    });

  /** ************************************************************** */
  /** ************************ Media player ***********************  */
  /** ************************************************************** */

  configuration
    .registerKey({ name: 'System API - media player' })
    .registerOnInitializeHandler((instance) => {
      log.info(
        `Instance with id:${instance.id} has been initialized with configuration:${JSON.stringify(instance.configuration)}`,
      );
    })
    .useSystemControlSystemMediaPlayer()
    .registerOnKeyUpHandler((instance) => {
      const random = Math.floor(Math.random() * 3 + 1);
      switch (random) {
        case 1:
          instance.setControlSystemMediaPlayer('play/pause');
          log.info(
            `Instance with id:${instance.id} has play/pause MediaPlayer`,
          );
          break;
        case 2:
          instance.setControlSystemMediaPlayer('previous');
          log.info(
            `Instance with id:${instance.id} has send previous to MediaPlayer`,
          );
          break;
        case 3:
          instance.setControlSystemMediaPlayer('next');
          log.info(
            `Instance with id:${instance.id} has send next to MediaPlayer`,
          );
          break;
        default:
          break;
      }
    })
    .registerOnDeactivateHandler((id) => {
      log.info(`Instance with id:${id} has been deactivated`);
    });

  /** ************************************************************** */
  /** ************************** Open app *************************  */
  /** ************************************************************** */

  configuration
    .registerKey({ name: 'System API - open application' }, 'win32') // Example of an action assigned to the windows platform
    .registerOnInitializeHandler((instance) => {
      log.info(
        `Instance with id:${instance.id} has been initialized with configuration:${JSON.stringify(instance.configuration)}`,
      );
    })
    .useOpenApp()
    .registerOnKeyUpHandler((instance) => {
      instance.openApp('Chrome'); // on win32
      log.info(`Instance with id:${instance.id} has open application Chrome`);
    })
    .registerOnDeactivateHandler((id) => {
      log.info(`Instance with id:${id} has been deactivated`);
    });

  configuration
    .registerKey({ name: 'System API - open application' }, 'darwin') // Example of an action assigned to the macOS platform
    .registerOnInitializeHandler((instance) => {
      log.info(
        `Instance with id:${instance.id} has been initialized with configuration:${JSON.stringify(instance.configuration)}`,
      );
    })
    .useOpenApp()
    .registerOnKeyUpHandler((instance) => {
      instance.openApp('com.google.Chrome'); // on macOS
      log.info(`Instance with id:${instance.id} has open application Chrome`);
    })
    .registerOnDeactivateHandler((id) => {
      log.info(`Instance with id:${id} has been deactivated`);
    });

  /** ************************************************************** */
  /** ************************ Key strokes ************************  */
  /** ************************************************************** */

  configuration
    .registerKey({ name: 'System API - keystrokes' })
    .registerOnInitializeHandler((instance) => {
      log.info(
        `Instance with id:${instance.id} has been initialized with configuration:${JSON.stringify(instance.configuration)}`,
      );
    })
    .addDropdown({
      key: 'selectedSystem',
      name: 'Select system',
      source: () => {
        return [
          { label: 'Windows', value: 1 },
          { label: 'macOS', value: 2 },
        ];
      },
    })
    .useKeystrokes()
    .registerOnKeyDownHandler((instance) => {
      const keystrokesMacOS = [
        { code: 'MetaLeft', keyCode: 55 },
        { code: 'KeyT', keyCode: 17 },
      ];
      const keystrokesWindowsOS = [
        { code: 'controlLeft', keyCode: 162 },
        { code: 'KeyT', keyCode: 84 },
      ];

      if (instance.configuration.selectedSystem) {
        const keystrokes =
          instance.configuration.selectedSystem === 2
            ? keystrokesMacOS
            : keystrokesWindowsOS;

        instance.pressKeystrokes(
          keystrokes.map(({ keyCode }) => keyCode),
          instance.configuration.selectedSystem === 2
            ? 'com.google.Chrome'
            : 'Chrome',
        );
        log.info(
          `Instance with id:${instance.id} has activated chrome, pressed keystrokes: ${JSON.stringify(keystrokes)} and return to previous active application`,
        );
      } else {
        log.info(
          `Instance with id:${instance.id} has no dropdown value selected. No action will be performed`,
        );
      }
    })
    .registerOnDeactivateHandler((id) => {
      log.info(`Instance with id:${id} has been deactivated`);
    });

  /** ************************************************************** */
  /** ************************ Display ************************  */
  /** ************************************************************** */
  const messagesApi = configuration.useMessages();

  configuration
    .registerDisplay({ name: 'slider' })
    .registerOnInitializeHandler((instance) => {
      log.info(`Instance slider:${instance.id} has been initialized.`);
    })
    .registerOnDeactivateHandler((instance) => {
      log.info(`Instance slider:${instance.id} has been deactivated.`);
    })
    .setSize(2, 1)
    .addLayer((layer) =>
      layer
        .setMargin(4, 4, 4, 4)
        .setBorderRadius(5, 5, 5, 5)
        .setBackgroundColor('#363636')
        .addDisplaySlider('sliderBar', (slider) =>
          slider
            .setSize(52, 112)
            .setColor('#6f6f6f')
            .setOrientation('vertical')
            .setBackgroundColor('#363636')
            .setIcon('volume_up')
            .setIconColor('#ffffff')
            .setIconBackgroundColor('#6f6f6f')
            .registerOnChangeHandler((value, instance) => {
              log.info(`Instance:${instance.id} value: ${value}`);
            }),
        ),
    );

  configuration
    .registerDisplay({ name: 'rowsAndColumns' })
    .registerOnInitializeHandler((instance) => {
      log.info(`Instance row:${instance.id} has been initialized.`);
    })
    .registerOnDeactivateHandler((instance) => {
      log.info(`Instance row:${instance.id} has been deactivated.`);
    })
    .setSize(2, 2)
    .addLayer((layer) =>
      layer
        .setMargin(4, 4, 4, 4)
        .setBorderRadius(5, 5, 5, 5)
        .setBackgroundColor('#6f6f6f')
        .addRow((row) =>
          row
            .setSize(114, 57)
            .addDisplayText('icon', (text) =>
              text
                .setMargin(4, 0, 4, 0)
                .setTextAlign('center')
                .setFontSize(36)
                .setFontWeight('bold')
                .setColor('#F9F9F9')
                .setText('row'),
            ),
        )
        .addRow((row) =>
          row
            .setSize(114, 57)
            .addColumn((column) =>
              column
                .setSize(57, 57)
                .setBackgroundColor('#363636')
                .addDisplayText('icon', (text) =>
                  text
                    .setMargin('auto', 'auto', 'auto', 'auto')
                    .setTextAlign('center')
                    .setFontSize(18)
                    .setFontWeight('bold')
                    .setColor('#F9F9F9')
                    .setText('column')
                    .setTextWrap('ellipsis'),
                ),
            )
            .addColumn((column) =>
              column
                .setSize(57, 57)
                .setBackgroundColor('#363636')
                .addDisplayText('icon', (text) =>
                  text
                    .setMargin(10, 'auto', 0, 'auto')
                    .setTextAlign('center')
                    .setFontSize(36)
                    .setFontWeight('bold')
                    .setColor('#F9F9F9')
                    .setText('splitscreen_left')
                    .setIsIcon(true),
                ),
            ),
        ),
    );

  configuration
    .registerDisplay({ name: 'events' })
    .registerOnInitializeHandler((instance) => {
      log.info(`Instance events:${instance.id} has been initialized.`);
    })
    .registerOnDeactivateHandler((instance) => {
      log.info(`Instance events:${instance.id} has been deactivated.`);
    })
    .setSize(2, 2)
    .addLayer((layer) =>
      layer
        .setMargin(4, 4, 4, 4)
        .setBorderRadius(5, 5, 5, 5)
        .setBackgroundColor('#6f6f6f')
        .addRow((row) =>
          row
            .setBackgroundColor('#363636')
            .setSize(114, 38)
            .addDisplayText('touchMove', (text) =>
              text
                .setMargin('auto', 'auto', 'auto', 'auto')
                .setTextAlign('center')
                .setFontSize(18)
                .setColor('#F9F9F9')
                .setText('Touch move'),
            )
            .registerOnTouchMoveHandler((value, instance) => {
              log.info(`Instance row:${instance.id} touch move event.`);
            }),
        )
        .addRow((row) =>
          row
            .setSize(114, 38)
            .addDisplayText('touchStart', (text) =>
              text
                .setMargin('auto', 'auto', 'auto', 'auto')
                .setTextAlign('center')
                .setFontSize(18)
                .setColor('#F9F9F9')
                .setText('Touch start'),
            )
            .registerOnTouchStartHandler((instance) => {
              log.info(`Instance row:${instance.id} touch start event.`);
            }),
        )
        .addRow((row) =>
          row
            .setBackgroundColor('#363636')
            .setSize(114, 38)
            .addDisplayText('touchMove', (text) =>
              text
                .setMargin('auto', 'auto', 'auto', 'auto')
                .setTextAlign('center')
                .setFontSize(18)
                .setColor('#F9F9F9')
                .setText('Touch end'),
            )
            .registerOnTouchEndHandler((instance) => {
              log.info(`Instance row:${instance.id} touch end event.`);
            }),
        ),
    );

  configuration
    .registerDisplay({ name: 'image2x2' })
    .registerOnInitializeHandler((instance) => {
      log.info(`Instance image:${instance.id} has been initialized.`);
    })
    .registerOnDeactivateHandler((instance) => {
      log.info(`Instance image:${instance.id} has been deactivated.`);
    })
    .setSize(2, 2)
    .addLayer((layer) =>
      layer
        .setMargin(4, 4, 4, 4)
        .setBorderRadius(5, 5, 5, 5)
        .setBackgroundColor('#6f6f6f')
        .addDisplayImage('image', (image) =>
          image.setSize(114, 114).setImageBase64Data(imageBase64),
        ),
    );

  // nie działa
  configuration
    .registerDisplay({ name: 'image1x1' })
    .registerOnInitializeHandler((instance) => {
      log.info(`Instance image:${instance.id} has been initialized.`);
    })
    .registerOnDeactivateHandler((instance) => {
      log.info(`Instance image:${instance.id} has been deactivated.`);
    })
    .setSize(1, 1)
    .addLayer((layer) =>
      layer
        .setMargin(4, 4, 4, 4)
        .setBorderRadius(5, 5, 5, 5)
        .setBackgroundColor('#6f6f6f')
        .addDisplayImage('image', (image) =>
          image.setSize(53, 53).setImageBase64Data(imageBase64),
        ),
    );

  configuration
    .registerDisplay({ name: 'message' })
    .registerOnInitializeHandler((instance) => {
      log.info(`Instance message:${instance.id} has been initialized.`);
    })
    .registerOnDeactivateHandler((instance) => {
      log.info(`Instance message:${instance.id} has been deactivated.`);
    })
    .setSize(1, 1)
    .addLayer((layer) =>
      layer
        .setMargin(4, 4, 4, 4)
        .setBorderRadius(5, 5, 5, 5)
        .setBackgroundColor('#6f6f6f')
        .addDisplayText('showMessage', (text) =>
          text
            .setMargin('auto', 'auto', 'auto', 'auto')
            .setTextAlign('center')
            .setFontSize(12)
            .setColor('#F9F9F9')
            .setText('Show message')
            .registerOnTouchStartHandler((instance) => {
              log.info(`Instance with id:${instance.id} has message event`);
              messagesApi.showMessage({
                title: 'title',
                message: 'message',
                disableCancelAction: true,
                actions: [
                  {
                    name: 'ok',
                    handler: () => {
                      log.info('handled ok action 2');
                    },
                  },
                ],
              });
            }),
        ),
    );
};

module.exports = boilerPlatePlugin;
