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

DOMAIN = {'events': events}
