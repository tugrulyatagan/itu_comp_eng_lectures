import bottle
import datetime
import pytz

@bottle.route("/")
def main():
    content = """
      <p>Show the time in:</p>
      <form action="/time" method="post">
        <input type="text" name="zone" />
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
