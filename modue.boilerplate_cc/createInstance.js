const createInstance = (jsInstance, actionName, log) => {
  return {
    jsInstance,
    actionName,

    get numberOfLeds() {
      if (this.jsInstance && typeof this.jsInstance.numberOfLeds === 'number') {
        return this.jsInstance.numberOfLeds;
      }
      log.error(
        `Property 'numberOfLeds' not found on the provided instance for widget: ${actionName}`,
      );
      return null; // Returning null if the property is not found
    },

    set(value) {
      if (this.jsInstance && typeof this.jsInstance.set === 'function') {
        try {
          this.jsInstance.set(value);
        } catch (error) {
          log.error(`Error executing instance.set: ${error.message}`);
        }
      } else {
        log.error(
          `set function not found on the provided instance for widget: ${actionName}`,
        );
      }
    },

    setSystemVolume(volume, deviceType, deviceId) {
      if (
        this.jsInstance &&
        typeof this.jsInstance.setSystemVolume === 'function'
      ) {
        log.info(`setSystemVolume: Maciej 1`);
        log.info(`setSystemVolume: ${volume}, ${deviceType}, ${deviceId}`);
        this.jsInstance.setSystemVolume(volume, deviceType, deviceId);
      } else {
        log.error(
          `setSystemVolume function not found for widget: ${actionName}`,
        );
      }
    },

    openApp(appId) {
      if (this.jsInstance && typeof this.jsInstance.openApp === 'function') {
        this.jsInstance.openApp(appId);
      } else {
        log.error(`openApp function not found for widget: ${actionName}`);
      }
    },

    muteMicrophone(deviceId) {
      if (
        this.jsInstance &&
        typeof this.jsInstance.muteMicrophone === 'function'
      ) {
        if (typeof deviceId === 'undefined' || deviceId === null) {
          this.jsInstance.muteMicrophone('');
        } else {
          this.jsInstance.muteMicrophone(deviceId);
        }
      } else {
        log.error(
          `muteMicrophone function not found for widget: ${actionName}`,
        );
      }
    },

    unmuteMicrophone(deviceId) {
      if (
        this.jsInstance &&
        typeof this.jsInstance.unmuteMicrophone === 'function'
      ) {
        if (typeof deviceId === 'undefined' || deviceId === null) {
          this.jsInstance.unmuteMicrophone('');
        } else {
          this.jsInstance.unmuteMicrophone(deviceId);
        }
      } else {
        log.error(
          `unmuteMicrophone function not found for widget: ${actionName}`,
        );
      }
    },

    takeScreenshot(saveLocation) {
      if (
        this.jsInstance &&
        typeof this.jsInstance.takeScreenshot === 'function'
      ) {
        this.jsInstance.takeScreenshot(saveLocation);
      } else {
        log.error(
          `takeScreenshot function not found for widget: ${actionName}`,
        );
      }
    },

    setControlSystemMediaPlayer(playerAction) {
      if (
        this.jsInstance &&
        typeof this.jsInstance.setControlSystemMediaPlayer === 'function'
      ) {
        this.jsInstance.setControlSystemMediaPlayer(playerAction);
      } else {
        log.error(
          `setControlSystemMediaPlayer function not found for widget: ${actionName}`,
        );
      }
    },

    pressKeystrokes(keyCodes, appId) {
      if (
        this.jsInstance &&
        typeof this.jsInstance.pressKeystrokes === 'function'
      ) {
        this.jsInstance.pressKeystrokes(keyCodes, appId);
      } else {
        log.error(
          `pressKeystrokes function not found for widget: ${actionName}`,
        );
      }
    },

    setAppVolume(volume, applicationId) {
      if (
        this.jsInstance &&
        this.jsInstance.windows &&
        typeof this.jsInstance.windows.setAppVolume === 'function'
      ) {
        this.jsInstance.windows.setAppVolume(volume, applicationId);
      } else {
        log.error(`setAppVolume function not found for widget: ${actionName}`);
      }
    },

    get applications() {
      if (this.jsInstance && this.jsInstance.applications) {
        return this.jsInstance.applications;
      }
      return null;
    },

    get availableAudioApplications() {
      if (this.jsInstance && this.jsInstance.availableAudioApplications) {
        return this.jsInstance.availableAudioApplications;
      }
      return null;
    },

    get microphones() {
      if (this.jsInstance && this.jsInstance.microphones) {
        return this.jsInstance.microphones;
      }
      return null;
    },

    get speakers() {
      if (this.jsInstance && this.jsInstance.speakers) {
        return this.jsInstance.speakers;
      }
      return null;
    },
  };
};

module.exports = { createInstance };
