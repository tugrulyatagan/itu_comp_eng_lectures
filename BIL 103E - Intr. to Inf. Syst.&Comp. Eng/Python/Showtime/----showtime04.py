import bottle
import datetime
import pytz

@bottle.route("/")
def main():
    page = """
      <p>Show me the time in:</p>
      <form action="/time" method="post">
        <select name="zone">
          <option value="Europe/Istanbul">Istanbul</option>
          <option value="Europe/Paris">Paris</option>
          <option value="Europe/London">London</option>
          <option value="America/New_York">New_York</option>
          <option value="Asia/Tokyo">Tokyo</option>
        </select>
        <input type="submit" value="Show" />
      </form>
      """
    return page

@bottle.route("/time", method="POST")
def display_time():
    zone_name = bottle.request.forms.zone
    timezone = pytz.timezone(zone_name)
    current_time = datetime.datetime.now(timezone)
    return "Current time in " + zone_name + " is " + str(current_time)

bottle.run(host='localhost', port=8080)
