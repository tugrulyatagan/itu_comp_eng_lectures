import bottle
import pytz
import datetime

@bottle.route("/time")
def say_time():
	local_time=datetime.datetime.now()
	eastern = pytz.timezone('US/Eastern')
	eastern_time=eastern.localize(local_time)
	return "%s" % eastern_time.strftime("%Y-%m-%d %H:%M:%S %Z%z") 

bottle.run(host='localhost', port=8080)
