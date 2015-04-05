from djazz import events
from eve import Eve
from djazz.interfaces import x10


# Event hook
def eventUpdated(updates, original):
    event = original.copy()
    event.update(updates)
    events.setCron(event)


# Thing hook
def thingUpdated(updates, original):
    thing = original.copy()
    thing.update(updates)
    address = x10.Addresses[thing['room']][thing['name']]
    x10.dim(address, thing['state']['level'])


app = Eve(settings='config/service_settings.py')
app.on_updated_events += eventUpdated
app.on_updated_things += thingUpdated


# If launched as script -> start the REST service
if __name__ == '__main__':
    # original = {
    #     'state': {'level': 21},
    #     'name': 'mainlights',
    #     'type': 'light',
    #     'room': 'living',
    #     '_id': '552142ed2083d605cb60b4f9'
    # }
    # updates = {
    #     'state': {'level': 0}
    # }
    # thingUpdated(updates, original)
    app.run(host='0.0.0.0')
