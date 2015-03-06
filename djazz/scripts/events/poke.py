from datetime import datetime

now = datetime.now()
filename = './poke_occurence_%s_%s_%s' % (now.hour, now.minute, now.second)
open(filename, 'a').close()
