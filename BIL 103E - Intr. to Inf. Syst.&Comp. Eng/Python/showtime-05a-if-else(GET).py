import bottle
import datetime
import pytz

@bottle.route("/")
def main():
    content = """
      <p>Show the time in:</p>
      <ul>
        <li><a href="/time?zone=Europe/Istanbul">Istanbul</a></li>
        <li><a href="/time?zone=Europe/London">London</a></li>
        <li><a href="/time?zone=Europe/Warsaw">Warsaw</a></li>
        <li><a href="/time?zone=America/New_York">New York</a></li>
        <li><a href="/time?zone=Asia/Tokyo">Tokyo</a></li>
      </ul>
    """
    return content

@bottle.route("/time", method="GET")
def get_time_message():
    if "zone" in bottle.request.GET:
        zone_name = bottle.request.GET.get("zone")
    else:
        zone_name = "Europe/Istanbul"
    timezone = pytz.timezone(zone_name)
    current_time = datetime.datetime.now(timezone)
    message = "Current time in " + zone_name + " is " + str(current_time)
    return message

bottle.run(host='localhost', port=8080)
