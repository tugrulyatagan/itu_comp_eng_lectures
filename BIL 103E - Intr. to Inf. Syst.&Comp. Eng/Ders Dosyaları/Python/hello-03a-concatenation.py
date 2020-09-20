import bottle

@bottle.route("/hello")
def get_hello_page():
    page = "<html>"
    page = page + "<head>"
    page = page + "<title>Hello</title>"
    page = page + "<meta http-equiv=\"Content-Type\""
    page = page + " content=\"text/html; charset=utf-8\" />"
    page = page + "</head>"
    page = page + "<body>"
    page = page + "<p>Hello, world!</p>"
    page = page + "</body>"
    page = page + "</html>"
    return page

bottle.run(host="localhost", port=8080)
