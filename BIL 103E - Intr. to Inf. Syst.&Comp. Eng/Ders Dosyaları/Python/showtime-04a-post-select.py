import bottle
import datetime
import pytz

@bottle.route("/")
def main():
    content = """
      <p>Show the time in:</p>
      <form action="/time" method="post">
        <select name="zone">
          <option value="Europe/Istanbul">Istanbul</option>
          <option value="Europe/London">London</option>
          <option value="Europe/Warsaw">Warsaw</option>
          <option value="America/New_York">New_York</option>
          <option value="Asia/Tokyo">Tokyo</option>
        </select>
        <input type="submit" value="Show" />
      </form>
    """
    return content

@bottle.route("/time", method="POST")
def get_time_message():
    zone_name = bottle.request.POST.get("zone")
    timezone = pytz.timezone(zone_name)
    current_time = datetime.datetime.now(timezone)
    message = "Current time in " + zone_name + " is " + str(current_time)
    return message

bottle.run(host='localhost', port=8080)
