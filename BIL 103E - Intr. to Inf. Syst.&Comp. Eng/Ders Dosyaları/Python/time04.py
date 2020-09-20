import bottle
import datetime

@bottle.route("/time")
def say_time():
	today = datetime.date.today()

	#out+="tuple:" + today.timetuple() + "<br/>"

	out= "%s %s %s" % ("today:" , today,"<br/>" )
	out+= "%s %s %s" % ("ctime:" , today.ctime(),"<br/>" )
	out+= "%s %s %s" % ("Year:", today.year,"<br/>" )
	out+= "%s %s %s" % ("Mon :", today.month,"<br/>" )
	out+= "%s %s %s" % ("Day :", today.day,"<br/>" )

	return out

bottle.run(host='localhost', port=8080)
