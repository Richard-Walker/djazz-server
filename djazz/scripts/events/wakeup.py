from datetime import datetime
from djazz.interfaces import x10, puz
from djazz.helpers import asyncFunc
from time import sleep


@asyncFunc
def dimLight():
    x10.dimOverPeriod(x10.Addresses.bedroomLight, 0, 100, minutes=30)


@asyncFunc
def essentialOils():
    puz.releaseScent(25 * 60)


print('{}: Dim start'.format(datetime.now()))
p1 = dimLight()

sleep(30)

print('{}: Spread of essential oils start'.format(datetime.now()))
p2 = essentialOils()

p2.join()
print('{}: Spread of essential oils end'.format(datetime.now()))

p1.join()
print('{}: Dim end'.format(datetime.now()))
