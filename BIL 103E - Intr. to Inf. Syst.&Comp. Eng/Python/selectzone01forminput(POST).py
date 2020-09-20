import bottle
import pytz

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
#    if zone:
#        if zone in pytz.all_timezones:
#            out="Selected zone is %s" % (zone)
#        else:
#            out="Please fill in a valid time zone"
#    else:
#        out="You missed a field."

    print pytz.all_timezones
    if not zone:
        out="You missed a field."
    elif zone not in pytz.all_timezones:
        out="Please fill in a valid time zone"
    else:
        out="Selected zone is %s" % (zone)
        

    return out

bottle.run(host='localhost', port=8080)