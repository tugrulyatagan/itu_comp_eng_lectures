import bottle
import datetime
import pytz

@bottle.route('/zone')
def select_zone():
    head="<html> <head> <title>Zone Selector</title> </head> <body> "
    body="""<p>Show me the time in:</p>
    <form action="zone" method="post">
    <select name="zone">
    <option value="Europe/Istanbul">Istanbul</option>
    <option value="Europe/Paris">Paris</option>
    <option value="Europe/London">London</option>
    <option value="America/New_York">New_York</option>
    <option value="Asia/Tokyo">Tokyo</option>
    </select>
    <input type="submit" value="Show" />
    </form>"""
    tail="</body> </html>"
    return head+body+tail

@bottle.route('/zone', method='POST')
def send_zone():
    #zone = bottle.request.forms.zone
    zone = bottle.request.forms.get('zone')
    if zone:
        myZone=pytz.timezone(zone)
    else:
        myZone=pytz.utc

    loc_dt = datetime.datetime.now(myZone)
    
    return loc_dt.strftime('%Y-%m-%d %H:%M:%S %Z%z')
    
bottle.run(host='localhost', port=8080)