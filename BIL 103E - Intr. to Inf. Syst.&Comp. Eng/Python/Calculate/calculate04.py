import bottle

@bottle.route("/calculate")
def calculate():
	a=8.0/3.0
	b='8/3'
    	return "%s = %3.4f" %(b,a)

bottle.run(host='localhost', port=8080)