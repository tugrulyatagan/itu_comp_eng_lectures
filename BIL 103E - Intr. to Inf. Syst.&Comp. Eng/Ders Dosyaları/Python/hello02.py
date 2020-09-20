import bottle

@bottle.route("/hello")
def say_hello():
    	out = "Hello"
	out = out + " world!"
    	return out

bottle.run(host='localhost', port=8080)
