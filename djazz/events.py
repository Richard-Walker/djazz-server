import os
from crontab import CronTab
from datetime import datetime


def setCron(event):
    cron = CronTab(user=True)

    # Get useful fields from event
    objectId = event['_id']
    time = event['time']
    name = event['name']
    enabled = event['enabled']

    # Build job command
    url = 'http://127.0.0.1:5000/events/%s' % objectId
    data = '\'{"enabled": false}\''
    header = '\'Content-Type: application/json\''
    cmdUpdate = 'curl -X PATCH -i %s -H %s -d %s' % (url, header, data)

    path = os.path.dirname(os.path.abspath(__file__))
    cmdScript = 'python %s/scripts/events/%s.py' % (path, name)
    logFile = '/var/log/djazz/event_%s.log' % name

    command = '%s; %s  >> %s 2>&1' % (cmdUpdate, cmdScript, logFile)

    # Find job from comment, create one if none
    comment = 'djazz_%s' % objectId
    job = next(cron.find_comment(comment), None)
    if job is None:
        job = cron.new(command=command, comment=comment)

    # Set cron options
    job.clear()
    job.setall(time.minute, time.hour, time.day, time.month, None)
    job.enable(enabled)

    # Commit changes
    cron.write()


# If launched as script -> execute test
if __name__ == '__main__':
    setCron({
        '_id': '000000ac2083d669b98ccdeb',
        'name': 'dummy',
        'enabled': False,
        'title': 'Dummy event',
        'time': datetime(2015, 1, 2, 3, 4)
    })
    print('Cron job set for dummy event')
