import datetime

def get_yesterday(): 
    today=datetime.datetime.today()
    dt = datetime.datetime(today.year, today.month, today.day, 0, 0, 0)
    print(dt)
    oneday=datetime.timedelta(days=1) 
    print(oneday)
    yesterday=dt-oneday  
    return yesterday

print get_yesterday()
print '------------------'
def get_time():
    #tm = datetime.time(23,10)
    tm = datetime.datetime.now()
    return tm.strftime("%H:%M")

print get_time()
