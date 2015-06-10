from subprocess import call
from enum import Enum


class Settings:
    cmd = '/usr/local/bin/pir'


IRCodes = {
    "marantz": {
        "power": '0000 0073 0000 0018 0020 0020 0020 0020 0020 0020 0040 0020 0020 0020 0020 0020 0020 0020 0020 0020 0020 0040 0020 0020 0040 0020 0020 0C5B 0020 0020 0020 0020 0020 0020 0040 0020 0020 0020 0020 0020 0020 0020 0020 0020 0020 0040 0020 0020 0040 0020 0020 0498',
        "test": '0000 0073 0000 0018 0020'
    }
}


class PirOut(Enum):
    main = 2
    cable = 1
    both = 3


def sendCode(code, output=PirOut.main, repeat=0):
    params = ["send", "all", code, str(output.value), str(repeat)]
    call([Settings.cmd] + params)


# If launched as script -> test sendCode() function
if __name__ == '__main__':
    sendCode(IRCodes['marantz']['power'], PirOut.cable)
