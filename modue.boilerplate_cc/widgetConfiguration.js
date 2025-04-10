const handleWidgetConfiguration = (
  widget,
  widgetActions,
  widgetId,
  cppPlugin,
  log,
) => {
  if (widgetActions.includes('addInput')) {
    const inputConfigs = cppPlugin.invokeAction(widgetId, 'addInput');

    if (inputConfigs) {
      for (let i = 0; i < inputConfigs.length; i++) {
        const inputConfig = inputConfigs[i];

        if (inputConfig && inputConfig.key) {
          widget.addInput(
            {
              key: inputConfig.key,
              name: inputConfig.name,
              description: inputConfig.description,
            },
            inputConfig.type,
          );

          log.info(
            `Registered input field: key=${inputConfig.key}, name=${inputConfig.name}, type=${inputConfig.type}`,
          );
        }
      }
    } else {
      log.info(`No input configurations found for widgetId: ${widgetId}`);
    }
  }

  if (widgetActions.includes('addDropdown')) {
    log.info(`Registered addDropdown for widgetId: ${widgetId}`);
  }

  if (widgetActions.includes('addButton')) {
    log.info(`Registered addButton for widgetId: ${widgetId}`);
  }

  if (widgetActions.includes('useInternalAuthorizationHandler')) {
    log.info(
      `Registered useInternalAuthorizationHandler for widgetId: ${widgetId}`,
    );
  }
};

module.exports = handleWidgetConfiguration;
