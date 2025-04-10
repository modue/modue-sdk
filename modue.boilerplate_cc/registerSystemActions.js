const registerSystemActions = (
  widget,
  widgetActions,
  widgetId,
  cppPlugin,
  assignInstance,
  log,
) => {
  if (widgetActions.includes('useSystemMuteMicrophone')) {
    widget.useSystemMuteMicrophone(() => {
      const result = cppPlugin.invokeAction(widgetId, 'useOpenApp');
      log.info(result);
    });
  }

  if (widgetActions.includes('useSystemUnmuteMicrophone')) {
    widget.useSystemUnmuteMicrophone(() => {
      const result = cppPlugin.invokeAction(widgetId, 'useOpenApp');
      log.info(result);
    });
  }

  if (widgetActions.includes('useSystemInstalledApps')) {
    widget.useSystemInstalledApps((apps, instance) => {
      const cppInstance = assignInstance(instance, 'useSystemInstalledApps');
      const result = cppPlugin.invokeAction(
        widgetId,
        'useSystemInstalledApps',
        cppInstance,
        apps,
      );
      log.info(result);
    });
  }

  if (widgetActions.includes('useAudioApps')) {
    widget.useAudioApps((audioAvailableApps, instance) => {
      const cppInstance = assignInstance(instance, 'useAudioApps');
      const result = cppPlugin.invokeAction(
        widgetId,
        'useAudioApps',
        cppInstance,
        audioAvailableApps,
      );
      log.info(result);
    });
  }

  if (widgetActions.includes('useSystemAvailableMicrophoneDevices')) {
    widget.useSystemAvailableMicrophoneDevices((microphones, instance) => {
      const cppInstance = assignInstance(
        instance,
        'useSystemAvailableMicrophoneDevices',
      );
      const result = cppPlugin.invokeAction(
        widgetId,
        'useSystemAvailableMicrophoneDevices',
        cppInstance,
        microphones,
      );
      log.info(result);
    });
  }

  if (widgetActions.includes('useSystemAvailableDevices')) {
    widget.useSystemAvailableMicrophoneDevices(
      (audioAvailableApps, instance) => {
        const cppInstance = assignInstance(
          instance,
          'useSystemAvailableDevices',
        );
        const result = cppPlugin.invokeAction(
          widgetId,
          'useSystemAvailableDevices',
          cppInstance,
          audioAvailableApps,
        );
        log.info(result);
      },
    );
  }

  if (widgetActions.includes('useSystemVolume')) {
    widget.useSystemVolume((value, instance) => {
      const cppInstance = assignInstance(instance, 'useSystemVolume');
      const result = cppPlugin.invokeAction(
        widgetId,
        'useSystemVolume',
        cppInstance,
        value,
      );
      log.info(result);
    });
  }

  if (widgetActions.includes('useMicrophoneSystemVolume')) {
    widget.useMicrophoneSystemVolume((value, instance) => {
      const cppInstance = assignInstance(instance, 'useMicrophoneSystemVolume');
      const result = cppPlugin.invokeAction(
        widgetId,
        'useMicrophoneSystemVolume',
        cppInstance,
        value,
      );
      log.info(result);
    });
  }

  if (widgetActions.includes('useSystemMonitorResources')) {
    widget.useSystemMonitorResources((resource, instance) => {
      const cppInstance = assignInstance(instance, 'useSystemMonitorResources');
      const result = cppPlugin.invokeAction(
        widgetId,
        'useSystemMonitorResources',
        cppInstance,
        resource,
      );
      log.info(result);
    });
  }

  if (widgetActions.includes('useSystemTakeScreenshot')) {
    widget.useSystemTakeScreenshot(() => {
      const result = cppPlugin.invokeAction(
        widgetId,
        'useSystemTakeScreenshot',
      );
      log.info(result);
    });
  }

  if (widgetActions.includes('useSystemControlSystemMediaPlayer')) {
    widget.useSystemControlSystemMediaPlayer(() => {
      const result = cppPlugin.invokeAction(widgetId, 'useOpenApp');
      log.info(result);
    });
  }

  if (widgetActions.includes('useOpenApp')) {
    widget.useOpenApp(() => {
      const result = cppPlugin.invokeAction(widgetId, 'useOpenApp');
      log.info(result);
    });
  }

  if (widgetActions.includes('useKeystrokes')) {
    widget.useKeystrokes(() => {
      const result = cppPlugin.invokeAction(widgetId, 'useKeystrokes');
      log.info(result);
    });
  }
};

module.exports = { registerSystemActions };
