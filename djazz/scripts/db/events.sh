# Delete events
curl -X DELETE -i http://127.0.0.1:5000/events 

# Delete crontab
# crontab -r

# Create events
curl -X POST -i http://127.0.0.1:5000/events -H 'Content-Type: application/json' -d '[{"name": "wakeup", "title": "Morning wake up"}]'
curl -X POST -i http://127.0.0.1:5000/events -H 'Content-Type: application/json' -d '[{"name": "poke", "title": "Home poke"}]'
