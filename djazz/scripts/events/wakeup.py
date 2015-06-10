from datetime import datetime
from djazz.interfaces import x10, puz
from djazz.helpers import asyncFunc
from time import sleep


@asyncFunc
def dimLight():
    address = x10.Addresses['bedroom']['mainlights']
    x10.dimOverPeriod(address, 0, 75, minutes=30)


@asyncFunc
def essentialOils():
    puz.releaseScent(30 * 60)


print('{}: Dim start'.format(datetime.now()))
p1 = dimLight()

sleep(15 * 60)

print('{}: Spread of essential oils start'.format(datetime.now()))
p2 = essentialOils()

p1.join()
print('{}: Dim end'.format(datetime.now()))

p2.join()
print('{}: Spread of essential oils end'.format(datetime.now()))
