import bottle
import datetime

@bottle.route("/time")
def get_time_message():
     current_time = datetime.datetime.now()
     message = "The current time is: " + str(current_time)
     return message

bottle.run(host="localhost", port=8080)

