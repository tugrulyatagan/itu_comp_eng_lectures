import bottle
import datetime
import pytz

@bottle.route("/time", method="GET")
def get_time_message():
    zone_name = bottle.request.GET.get("zone")
    timezone = pytz.timezone(zone_name)
    current_time = datetime.datetime.now(timezone)
    message = "Current time in " + zone_name + " is " + str(current_time)
    return message

bottle.run(host='localhost', port=8080)
