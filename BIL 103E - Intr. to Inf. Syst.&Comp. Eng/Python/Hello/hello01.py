import bottle

@bottle.route("/hello")
def say_hello():
	#This is a comment
	print("Hello World!")
	return "<h1>Hello World</h1>"

bottle.run(host='localhost', port=8080)
