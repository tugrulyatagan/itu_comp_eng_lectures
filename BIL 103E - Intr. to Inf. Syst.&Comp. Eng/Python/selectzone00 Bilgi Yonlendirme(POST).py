import bottle

@bottle.route('/zone')
def select_zone():
    head="<html> <head> <title>Zone Selector</title> </head> <body> "
    body="""
        <p>Show me the time in:</p>
        <form action="zone" method="post">
        <input type="text" name="zone" />
        <input type="submit" value="Show" />
        </form>"""

    tail="</body> </html>"
    return head+body+tail

@bottle.route('/zone', method='POST')
def send_zone():
    #zone = bottle.request.forms.zone
    zone = bottle.request.forms.get('zone')
    if zone:
        return "Selected zone is %s" % (zone)
    return "You missed a field."

bottle.run(host='localhost', port=8080)