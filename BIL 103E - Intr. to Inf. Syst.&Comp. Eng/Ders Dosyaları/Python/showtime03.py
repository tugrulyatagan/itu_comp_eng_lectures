import bottle
import datetime
import pytz

@bottle.route("/")
def main():
    page = """
      <p>Show me the time in:</p>
      <form action="/time" method="post">
        <input type="text" name="zone" />
        <input type="submit" value="Show" />
      </form>
      """
    return page

@bottle.route("/time", method="POST")
def display_time():
    zone_name = bottle.request.forms.zone
    
    if zone_name:
        timezone = pytz.timezone(zone_name)
        current_time = datetime.datetime.now(timezone)
        return "Current time in " + zone_name + " is " + str(current_time)

    return "Please enter a timezone!"

bottle.run(host='localhost', port=8080)
