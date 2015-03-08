import RPi.GPIO as GPIO
import time


puzhenPin = 26


def startStop():
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(puzhenPin, GPIO.OUT)

    GPIO.output(puzhenPin, 1)
    time.sleep(1)
    GPIO.output(puzhenPin, 0)

    GPIO.cleanup()


# If launched as script -> send startStop RF command
if __name__ == '__main__':
    startStop()
