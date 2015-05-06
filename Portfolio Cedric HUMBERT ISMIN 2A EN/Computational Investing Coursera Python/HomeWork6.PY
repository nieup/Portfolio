import pandas as pd
import numpy as np
import QSTK.qstkutil.qsdateutil as du
import datetime as dt
import math
import copy
import QSTK.qstkutil.qsdateutil as du
import datetime as dt
import QSTK.qstkutil.DataAccess as da
import QSTK.qstkutil.tsutil as tsu
import QSTK.qstkstudy.EventProfiler as ep


### SETTING VARIABLES :

## TIME : 
# Start and End date 
dt_start = dt.datetime(2008,1,1) ## ENTER DATE 
dt_end = dt.datetime(2009,12,31)## ENTER DATE

# We need closing prices so the timestamp should be hours=16.
dt_timeofday = dt.timedelta(hours=16)

# Get a list of trading days between the start and the end.
ldt_timestamps = du.getNYSEdays(dt_start, dt_end, dt_timeofday)

## ENVENT PROFILING :
event_lvl = -2.0 # Level of the event
M_event_lvl = 1.4 # Level of the Market Event 

# Rolling days :
Roll_D = 20


## EVENT REFERENCING :


print "Downloading Data" 

dataobj = da.DataAccess('Yahoo')
ls_symbols = dataobj.get_symbols_from_list('SP5002012')
ls_symbols.append('SPY') ## Note 

print "Extracting Data" 


#Extracting data 
ls_keys = ['actual_close', 'close']
ldf_data = dataobj.get_data(ldt_timestamps, ls_symbols, ls_keys)
d_data = dict(zip(ls_keys, ldf_data))

print "Removing NANs"

#Removing NANs 
for s_key in ls_keys:
    d_data[s_key] = d_data[s_key].fillna(method='ffill')
    d_data[s_key] = d_data[s_key].fillna(method='bfill')
    d_data[s_key] = d_data[s_key].fillna(1.0)

''' Finding the event dataframe '''
df_close = d_data['close'] ## NOTE 
ts_market = df_close['SPY']

# Creating an empty dataframe
df_events = copy.deepcopy(df_close)
df_events = df_events * np.NAN

# Time stamps for the event range
#ldt_timestamps = df_close.index

def do(s_sym, inD):
    t_price = []
 
    for i in range(1, Roll_D):
        t_price = t_price + [df_close[s_sym].ix[ldt_timestamps[inD - i + 1 ]]]

    mean = np.mean(t_price)
    Dev = np.std(t_price)
    Bol = (df_close[s_sym].ix[ldt_timestamps[inD]] - mean) / Dev
    # print Bol
    return Bol #, mean, Dev, df_close[s_sym].ix[dt_day]



j = 0

f_bollinger_Market = [0]

for i in range(1, len(ldt_timestamps)):
    f_bollinger_Market = f_bollinger_Market + [do('SPY', i)]
    #print f_bollinger_Market[i-1]
print "SPY is done" 


print "Finding Events"

count = 0
f_bollinger_today = 0

for s_sym in ls_symbols:
    if (j == len(ldt_timestamps) / 3):
        print "1/3 through"
    if (j == len(ldt_timestamps) * 3 / 5):
        print "3/5 through"
    if (j == len(ldt_timestamps) * 7 / 8):
        print "7/8 through"

    for i in range(1, len(ldt_timestamps)):
        if i > 85 :
            if f_bollinger_Market[i] >= M_event_lvl:
                # Calculating the returns for this timestamp
                f_bollinger_today = do(s_sym, i)
                f_bollinger_yesterday = do(s_sym, i-1)
                # Event is found if the symbol felt to event_lvl$ on that day 
                if f_bollinger_today < event_lvl and \
                f_bollinger_yesterday >= event_lvl:
                    df_events[s_sym].ix[ldt_timestamps[i]] = 1
                    count = count + 1
    j = j + 1

    
"""

for s_sym in ls_symbols:
    if (j == len(ldt_timestamps) / 3):
        print "1/3 through"
    if (j == len(ldt_timestamps) * 3 / 5):
        print "3/5 through"
    if (j == len(ldt_timestamps) * 7 / 8):
        print "7/8 through"

    for i in range(1, len(ldt_timestamps)):
        if i >= 20:
            if f_bollinger_Market[i-1] >= M_event_lvl:
                # Calculating the returns for this timestamp
                f_bollinger_today = ([df_close[s_sym].ix[ldt_timestamps[i]]] -
                                    pd.rolling_mean([df_close[s_sym].ix[ldt_timestamps[i]]],20))/ pd.rolling_std([df_close[s_sym].ix[ldt_timestamps[i]]], 20)
                if f_bollinger_today <= event_lvl :
                                if f_bollinger_y >= event_lvl:
                                    df_events[s_sym].ix[ldt_timestamps[i]] = 1
                                    count = count + 1
                                    f_bollinger_y = f_bollinger_today 
    j = j + 1 
                        
"""

print "Creating plot : "
ep.eventprofiler(df_events, d_data, i_lookback=20, i_lookforward=20,
                 s_filename='MyEventStudyHQ6.pdf', b_market_neutral=True, b_errorbars=True,
                 s_market_sym='SPY')

print "Done"









