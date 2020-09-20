import bottle

@bottle.route("/hello")
def say_hello():
    output = """
      <html>
        <head>
          <title>Hello</title>
          <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
        </head>
        <body>
          <p>Hello world!</p>
        </body>
      </html>
    """
    return output

bottle.run(host='localhost', port=8080)
