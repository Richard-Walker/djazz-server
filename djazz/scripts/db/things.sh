# Delete
# curl -X DELETE -i http://127.0.0.1:5000/things 

# Create
# curl -X POST -i http://127.0.0.1:5000/things -H 'Content-Type: application/json' -d '[{"room": "living", "name": "mainlights", "type": "light", "state": {"level": 0} }]'
# curl -X POST -i http://127.0.0.1:5000/things -H 'Content-Type: application/json' -d '[{"room": "living", "name": "moonlights", "type": "light", "state": {"level": 0} }]'
curl -X POST -i http://127.0.0.1:5000/things -H 'Content-Type: application/json' -d '[{"room": "bedroom", "name": "mainlights", "type": "light", "state": {"level": 0} }]'
