import bottle

@bottle.route("/hello")
def get_hello_page():
    page = "<html>\n"
    page = page + "  <head>\n"
    page = page + "    <title>Hello</title>\n"
    page = page + "    <meta http-equiv=\"Content-Type\"\n"
    page = page + "          content=\"text/html; charset=utf-8\" />\n"
    page = page + "  </head>\n"
    page = page + "  <body>\n"
    page = page + "    <p>Hello, world!</p>\n"
    page = page + "  </body>\n"
    page = page + "</html>\n"
    return page

bottle.run(host="localhost", port=8080)
