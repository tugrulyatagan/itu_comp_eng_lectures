import bottle
import time

@bottle.route("/time")
def say_time():
    return "%s" % time.strftime('%X %x %Z') 

bottle.run(host='localhost', port=8080)
