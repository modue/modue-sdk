const boilerPlatePlugin = (configuration, storage, log) => {
  /** ************************************************************** */
  /** **************** Simple change event example ****************  */
  /** ************************************************************** */

  configuration
    .registerSlider({ name: 'Basic - slider change event' })
    .registerOnInitializeHandler((instance, initialState) => {
      log.info(
        `Instance with id:${instance.id} has been initialized with state:${JSON.stringify(initialState)}`,
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
    .registerOnInitializeHandler((instance, initialState) => {
      log.info(
        `Instance with id:${instance.id} has been initialized with state:${JSON.stringify(initialState)}`,
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
    .registerOnInitializeHandler((instance, initialState) => {
      log.info(
        `Instance with id:${instance.id} has been initialized with state:${JSON.stringify(initialState)}`,
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
    .registerOnInitializeHandler((instance, initialState) => {
      log.info(
        `Instance with id:${instance.id} has been initialized with state:${JSON.stringify(initialState)}`,
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
    .registerOnInitializeHandler((instance, initialState) => {
      log.info(
        `Instance with id:${instance.id} has been initialized with state:${JSON.stringify(initialState)}`,
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
    .registerOnInitializeHandler((instance, initialState) => {
      log.info(
        `Instance with id:${instance.id} has been initialized with state:${JSON.stringify(initialState)}`,
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
    .registerOnInitializeHandler((instance, initialState) => {
      log.info(
        `Instance with id:${instance.id} has been initialized with state:${JSON.stringify(initialState)}`,
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
    .registerOnInitializeHandler((instance, initialState) => {
      log.info(
        `Instance with id:${instance.id} has been initialized with state:${JSON.stringify(initialState)}`,
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
    .registerOnInitializeHandler((instance, initialState) => {
      log.info(
        `Instance with id:${instance.id} has been initialized with state:${JSON.stringify(initialState)}`,
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
    .registerOnInitializeHandler((instance, initialState) => {
      log.info(
        `Instance with id:${instance.id} has been initialized with state:${JSON.stringify(initialState)}`,
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
    .registerOnInitializeHandler((instance, initialState) => {
      log.info(
        `Instance with id:${instance.id} has been initialized with state:${JSON.stringify(initialState)}`,
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
    .registerOnInitializeHandler((instance, initialState) => {
      log.info(
        `Instance with id:${instance.id} has been initialized with state:${JSON.stringify(initialState)}`,
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
    .registerOnInitializeHandler((instance, initialState) => {
      log.info(
        `Instance with id:${instance.id} has been initialized with state:${JSON.stringify(initialState)}`,
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
    .registerOnInitializeHandler((instance, initialState) => {
      log.info(
        `Instance with id:${instance.id} has been initialized with state:${JSON.stringify(initialState)}`,
      );
    })
    .registerOnChangeHandler((value, instance) => {
      log.info(
        `Instance with id:${instance.id} has set microphone volume to ${value}`,
      );
      instance.setSystemVolume(value, 'Mike'); // Set the volume of the default microphone device
    })
    .useSystemVolume(() => {})
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
    .registerOnInitializeHandler((instance, initialState) => {
      log.info(
        `Instance with id:${instance.id} has been initialized with state:${JSON.stringify(initialState)}`,
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
    .registerOnInitializeHandler((instance, initialState) => {
      log.info(
        `Instance with id:${instance.id} has been initialized with state:${JSON.stringify(initialState)}`,
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
    .registerOnInitializeHandler((instance, initialState) => {
      log.info(
        `Instance with id:${instance.id} has been initialized with state:${JSON.stringify(initialState)}`,
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
    .registerOnInitializeHandler((instance, initialState) => {
      log.info(
        `Instance with id:${instance.id} has been initialized with state:${JSON.stringify(initialState)}`,
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
    .registerOnInitializeHandler((instance, initialState) => {
      log.info(
        `Instance with id:${instance.id} has been initialized with state:${JSON.stringify(initialState)}`,
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
    .registerOnInitializeHandler((instance, initialState) => {
      log.info(
        `Instance with id:${instance.id} has been initialized with state:${JSON.stringify(initialState)}`,
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
      const keystrokes = [
        { code: 'MetaLeft', keyCode: 55 },
        { code: 'KeyT', keyCode: 17 },
      ];
      if (instance.configuration.selectedSystem) {
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
};

module.exports = boilerPlatePlugin;
