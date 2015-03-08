from datetime import datetime
from djazz.interfaces import x10
from djazz.helpers import asyncFunc


@asyncFunc
def dimLight():
    x10.dimOverPeriod(x10.Addresses.bedroomLight, 0, 100, minutes=30)


print('{}: Starting wakeup routine'.format(datetime.now()))
p = dimLight()
p.join()
print('{}: Wakeup routine finished'.format(datetime.now()))
