from datetime import datetime

MONGO_USERNAME = 'mongoUser'
MONGO_PASSWORD = 'Trustno1'
MONGO_DBNAME = 'djazz'

HATEOAS = False
IF_MATCH = False
DATE_FORMAT = "%Y-%m-%d %H:%M:%S %z"

RESOURCE_METHODS = ['GET', 'POST', 'DELETE']
ITEM_METHODS = ['GET', 'PATCH', 'PUT', 'DELETE']

CACHE_CONTROL = "private, max-age=0, no-cache"

# ------ EVENTS ----------------------------------

eventSchema = {
    # Schema definition, based on Cerberus grammar. Check the Cerberus project
    # (https://github.com/nicolaiarocci/cerberus) for details.
    'name': {
        'type': 'string',
        'minlength': 1,
        'maxlength': 15,
        'required': True,
        'unique': True,
    },
    'title': {
        'type': 'string',
        'minlength': 1,
        'required': True
    },
    'time': {
        'type': 'datetime',
        'default': datetime.now()
    },
    'enabled': {
        'type': 'boolean',
        'default': False
    }
}

events = {
    'additional_lookup': {
        'url': 'regex("[\w]+")',
        'field': 'name'
    },
    'schema': eventSchema
}

# ------ THINGS ----------------------------------

thingStateSchema = {
    # Lights
    'level': {
        'type': 'integer',
        'required': False,
        'min': 0,
        'max': 100
    }
}

thingSchema = {
    'name': {
        'type': 'string',
        'required': True
    },
    'room': {
        'type': 'string',
        'required': True
    },
    'type': {
        'type': 'string',
        'required': True,
        'allowed': ['light']
    },
    'state': {
        'type': 'dict',
        'schema': thingStateSchema,
        'required': True
    }
}

things = {
    'schema': thingSchema
}

DOMAIN = {
    'events': events,
    'things': things
}
