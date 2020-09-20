import bottle
import datetime
import pytz

@bottle.route('/zone')
def select_zone():
    head="<html> <head> <title>Zone Selector</title> </head> <body> "
    body="""<p>Show me the time in:</p>
    <form action="zone" method="post">
    <select name="zone">"""

    for tzone in pytz.common_timezones:
		body = body + "<option value=\"" + tzone +"\">" + tzone + "</option>"

    for tzone in pytz.common_timezones:
		regions=tzone.split('/')
		if regions[0] == "UTC":
			region="UTC"
		elif regions[0] == "GMT":
			region="GMT"
		else:
			region=regions[1].replace('_',' ')
		body+="<option value=\"" + tzone +"\">" + region + "</option>"

    for tzone in pytz.common_timezones:
		regions=tzone.split('/')
		region=regions[len(regions)-1]
		region=region.replace('_',' ')
		body+="<option value=\"" + tzone +"\">" + region + "</option>"
    body= body + """</select>
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
