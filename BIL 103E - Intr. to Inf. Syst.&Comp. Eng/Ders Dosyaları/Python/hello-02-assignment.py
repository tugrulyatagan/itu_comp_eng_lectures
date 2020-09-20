import bottle

@bottle.route("/hello")
def get_hello_message():
    message = "Hello, world!"
    return message

bottle.run(host='localhost', port=8080)
