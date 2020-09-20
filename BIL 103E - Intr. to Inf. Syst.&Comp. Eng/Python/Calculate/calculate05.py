import bottle

@bottle.route("/calculate")
def calculate():
	c=1.5+0.5j
    	#return "%s" %c
	return "%s+%sj"% (c.real,c.imag)

bottle.run(host='localhost', port=8080)