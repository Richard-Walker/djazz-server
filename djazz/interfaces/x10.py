from enum import Enum
from subprocess import call
from djazz.helpers import timeLapses


class Settings:
    cmd = '/usr/local/bin/heyu'


class Addresses:
    livingLights = 'F8'
    bedroomLight = 'F9'


class DimSpeed(Enum):
    fast = 0      # 3.7 sec
    slow = 1      # 30 sec
    slower = 2    # 1 min
    slowest = 3   # 5 min


def dim(address, level, speed=DimSpeed.fast):
    # Converts a perception level (%) into the corresponding system level (%)
    def sysLevel(level): return ((level / 100) ** 2) * 100
    levelCode = int(round(sysLevel(level) * 62 / 100))
    data = speed.value * 0x40 + levelCode
    call([Settings.cmd, 'xfunc 31 {} {:02X}'.format(address, data)])


def dimOverPeriod(address, originLevel, targetLevel, minutes):
    level = originLevel
    levelIncrement = (targetLevel - originLevel) / minutes
    for t in timeLapses(60, count=minutes):
        level += levelIncrement
        dim(address, level, DimSpeed.slower)


# If launched as script -> test dim() function
if __name__ == '__main__':
    dim(Addresses.livingLights, 50, DimSpeed.slow)
    # dimOverPeriod(Addresses.livingLights, 0, 100, 30)
