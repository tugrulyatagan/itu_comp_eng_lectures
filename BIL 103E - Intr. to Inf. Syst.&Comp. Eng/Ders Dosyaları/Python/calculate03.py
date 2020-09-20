import bottle

@bottle.route("/calculate")
def calculate():
	a=8.0/3.0
    	#return "%d" % a
    	return "%f" % a

bottle.run(host='localhost', port=8080)