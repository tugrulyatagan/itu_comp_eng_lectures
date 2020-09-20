import bottle
import datetime
import pytz

@bottle.route('/zone')
def select_zone():
    head="<html> <head> <title>Zone Selector</title> </head> <body> "
    body="""<p>Show me the time in:</p>
    <form action="zone" method="post">
    <select name="zones" multiple="multiple">
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
    zones = bottle.request.forms.getlist('zone')

    out=""
    zone_count=len(zones)
    if zone_count==0:
		return "Please select a time zone"
		
    count=0
    while(count<zone_count):
        tzone=zones[count]
        myZone=pytz.timezone(tzone)
        loc_dt = datetime.datetime.now(myZone)
        out=out+"Local time in "+ tzone +" is: "+ loc_dt.strftime('%Y-%m-%d %H:%M:%S %Z%z') + "<br/>"
        count=count+1
        
    return out
    
bottle.run(host='localhost', port=8080)
