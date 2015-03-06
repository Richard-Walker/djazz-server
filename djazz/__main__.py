from djazz import events
from eve import Eve


# Event hook
def eventUpdated(updates, original):
    event = original.copy()
    event.update(updates)
    events.setCron(event)


app = Eve(settings='config/service_settings.py')
app.on_updated_events += eventUpdated

# If launched as script -> start the REST service
if __name__ == '__main__':
    app.run(host='0.0.0.0')
