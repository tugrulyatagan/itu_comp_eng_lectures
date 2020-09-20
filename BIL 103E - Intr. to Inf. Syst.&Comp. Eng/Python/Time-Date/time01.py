import bottle
import time

@bottle.route("/time")
def say_time():
    return "%d" % time.time()

bottle.run(host='localhost', port=8080)