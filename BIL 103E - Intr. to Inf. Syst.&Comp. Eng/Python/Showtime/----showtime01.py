import bottle
import datetime
import pytz

@bottle.route("/time", method="GET")
def display_time():
    zone_name = bottle.request.query.zone
    timezone = pytz.timezone(zone_name)
    current_time = datetime.datetime.now(timezone)
    return "Current time in " + zone_name + " is " + str(current_time)

bottle.run(host='localhost', port=8080)
