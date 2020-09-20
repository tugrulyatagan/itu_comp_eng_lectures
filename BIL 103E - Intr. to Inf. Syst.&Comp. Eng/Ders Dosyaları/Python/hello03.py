import bottle

@bottle.route("/hello")
def say_hello():
    output = "<html>"
    output = output + "<head>"
    output = output + "<title>Hello</title>"
    output = output + "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />"
    output = output + "</head>"
    output = output + "<body>"
    output = output + "<p>Hello world!</p>"
    output = output + "</body>"
    output = output + "</html>"
    return output

bottle.run(host='localhost', port=8080)
