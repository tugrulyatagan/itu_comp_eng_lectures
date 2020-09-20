import bottle
import time

@bottle.route("/time")
def say_time():
    	#return "%s" % time.strftime("%d %b %Y %I:%M:%S %p") 
	return "%s" % time.strftime("%Y-%m-%d %H:%M:%S")
 
bottle.run(host='localhost', port=8080)
