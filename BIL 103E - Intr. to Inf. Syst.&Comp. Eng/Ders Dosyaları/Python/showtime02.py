import bottle
import datetime
import pytz

@bottle.route("/")
def main():
    page = """
      <p>Show me the time in:</p>
      <ul>
        <li><a href="/time?zone=Europe/Istanbul">Istanbul</a></li>
        <li><a href="/time?zone=Europe/Paris">Paris</a></li>
        <li><a href="/time?zone=Europe/London">London</a></li>
        <li><a href="/time?zone=America/New_York">New York</a></li>
        <li><a href="/time?zone=Asia/Tokyo">Tokyo</a></li>
      </ul>
      """
    return page

@bottle.route("/time", method="GET")
def display_time():
    zone_name = bottle.request.query.zone
    timezone = pytz.timezone(zone_name)
    current_time = datetime.datetime.now(timezone)
    return "Current time in " + zone_name + " is " + str(current_time)

bottle.run(host='localhost', port=8080)
