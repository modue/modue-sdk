const addon = require('bindings')('plugin');
const { createInstance } = require('./createInstance');
const { registerSystemActions } = require('./registerSystemActions');
const handleWidgetConfiguration = require('./widgetConfiguration');

const boilerPlatePlugin = (configuration, storage, log) => {
  const cppPlugin = new addon.Plugin();
  const cppConfiguration = cppPlugin.getConfiguration();

  Object.keys(cppConfiguration).forEach((widgetId) => {
    const widgetConfig = cppConfiguration[widgetId];
    if (!widgetConfig || !widgetConfig.name) {
      log.info('Widget is missing a name');
      return;
    }

    const widgetName = widgetConfig.name;
    const widgetType = widgetConfig.type;
    const widgetActions = widgetConfig.actions;

    const assignInstance = (jsInstance, actionName) => {
      return createInstance(jsInstance, actionName, log);
    };

    let widget;
    switch (widgetType) {
      case 'Slider':
        widget = configuration.registerSlider({ name: widgetName });
        break;
      case 'Key':
        widget = configuration.registerKey({ name: widgetName });
        break;
      case 'Knob':
        widget = configuration.registerKnob({ name: widgetName });
        break;
      case 'Switch':
        widget = configuration.registerSwitch({ name: widgetName });
        break;
      case 'LedCluster':
        widget = configuration.registerLedCluster({ name: widgetName });
        break;
      default:
        log.info(`Unknown widget type: ${widgetName}`);
        return;
    }

    // Register handlers based on available actions
    if (widgetActions.includes('registerOnInitializeHandler')) {
      widget.registerOnInitializeHandler((instance) => {
        const cppInstance = assignInstance(
          instance,
          'registerOnInitializeHandler',
        );
        const result = cppPlugin.invokeAction(
          widgetId,
          'registerOnInitializeHandler',
          cppInstance,
        );
        log.info(result);
      });
    }

    if (widgetActions.includes('registerOnChangeHandler')) {
      widget.registerOnChangeHandler((value, instance) => {
        const cppInstance = assignInstance(instance, 'registerOnChangeHandler');
        const result = cppPlugin.invokeAction(
          widgetId,
          'registerOnChangeHandler',
          cppInstance,
          value,
        );
        log.info(result);
      });
    }

    if (widgetActions.includes('registerOnDeactivateHandler')) {
      widget.registerOnDeactivateHandler((id) => {
        const result = cppPlugin.invokeAction(
          widgetId,
          'registerOnDeactivateHandler',
          id.toString(),
        );
        log.info(result);
      });
    }

    if (widgetActions.includes('registerOnConfigurationChangeHandler')) {
      widget.registerOnConfigurationChangeHandler((newConfig, instance) => {
        const cppInstance = assignInstance(
          instance,
          'registerOnConfigurationChangeHandler',
        );
        const result = cppPlugin.invokeAction(
          widgetId,
          'registerOnConfigurationChangeHandler',
          cppInstance,
          newConfig,
        );
        log.info(result);
      });
    }

    if (widgetType === 'Key') {
      if (widgetActions.includes('registerOnKeyDownHandler')) {
        widget.registerOnKeyDownHandler((instance) => {
          const cppInstance = assignInstance(
            instance,
            'registerOnKeyDownHandler',
          );
          const result = cppPlugin.invokeAction(
            widgetId,
            'registerOnKeyDownHandler',
            cppInstance,
          );
          log.info(result);
        });
      }

      if (widgetActions.includes('registerOnKeyUpHandler')) {
        widget.registerOnKeyUpHandler((instance) => {
          const cppInstance = assignInstance(
            instance,
            'registerOnKeyUpHandler',
          );
          const result = cppPlugin.invokeAction(
            widgetId,
            'registerOnKeyUpHandler',
            cppInstance,
          );
          log.info(result);
        });
      }
    }

    handleWidgetConfiguration(widget, widgetActions, widgetId, cppPlugin, log);

    registerSystemActions(
      widget,
      widgetActions,
      widgetId,
      cppPlugin,
      assignInstance,
      log,
    );
  });
};

module.exports = boilerPlatePlugin;
