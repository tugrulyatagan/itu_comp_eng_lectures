import bottle

@bottle.route("/hello")
def get_hello_page():
    page = """
      <html>
        <head>
          <title>Hello</title>
          <meta http-equiv="Content-Type"
                content="text/html; charset=utf-8" />
        </head>
        <body>
          <p>Hello, world!</p>
        </body>
      </html>
    """
    return page

bottle.run(host="localhost", port=8080)
