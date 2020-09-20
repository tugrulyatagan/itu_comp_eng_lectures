import bottle

@bottle.route("/calculate")
def calculate():
    	return 3+5

bottle.run(host='localhost', port=8080)