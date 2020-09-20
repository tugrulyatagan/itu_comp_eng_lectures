import bottle

@bottle.route("/calculate")
def calculate():
	a=3+5
    	return "0-(3+5)=%d" % -a

bottle.run(host='localhost', port=8080)