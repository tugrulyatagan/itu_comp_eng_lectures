import bottle

@bottle.route("/hello")
def get_hello_message():
    return "Hello, world!"

bottle.run(host='localhost', port=8080)
