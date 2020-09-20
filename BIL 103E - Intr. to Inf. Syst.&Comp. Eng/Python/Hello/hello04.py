import bottle

@bottle.route("/hello")
def say_hello():
    output = "<html>\n"
    output = output + "  <head>\n"
    output = output + "    <title>Hello</title>\n"
    output = output + "    <meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\n"
    output = output + "  </head>\n"
    output = output + "  <body>\n"
    output = output + "    <p>Hello world!</p>\n"
    output = output + "  </body>\n"
    output = output + "</html>\n"
    return output

bottle.run(host='localhost', port=8080)
