import RPi.GPIO as GPIO
from time import sleep


class Settings:
    pin = 26


def startStop():
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(Settings.pin, GPIO.OUT)

    GPIO.output(Settings.pin, 1)
    sleep(1)
    GPIO.output(Settings.pin, 0)

    GPIO.cleanup()


def releaseScent(duration):
    startStop()
    sleep(duration)
    startStop()


# If launched as script -> test releaseScent() function
if __name__ == '__main__':
    releaseScent(10)
