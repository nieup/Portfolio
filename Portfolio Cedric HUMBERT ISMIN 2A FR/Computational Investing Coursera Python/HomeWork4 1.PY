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

dt_start = dt.datetime(2008, 1, 1)
dt_end = dt.datetime(2009, 12, 31)
event_lvl = 6.0


print "Downloading Data" 

dataobj = da.DataAccess('Yahoo')
ls_symbols = dataobj.get_symbols_from_list('sp5002012')
ls_symbols.append('SPY')

print "Extracting Data" 

ldt_timestamps = du.getNYSEdays(dt_start, dt_end, dt.timedelta(hours=16))

#Extracting data 
ls_keys = ['actual_close']
ldf_data = dataobj.get_data(ldt_timestamps, ls_symbols, ls_keys)
d_data = dict(zip(ls_keys, ldf_data))

print "Removing NANs"

#Removing NANs 
for s_key in ls_keys:
    d_data[s_key] = d_data[s_key].fillna(method='ffill')
    d_data[s_key] = d_data[s_key].fillna(method='bfill')
    d_data[s_key] = d_data[s_key].fillna(1.0)

''' Finding the event dataframe '''
df_close = d_data['actual_close']
# ts_market = df_close['SPY']

print "Finding Events"

# Creating an empty dataframe
df_events = copy.deepcopy(df_close)
df_events = df_events * np.NAN

# Time stamps for the event range
ldt_timestamps = df_close.index

for s_sym in ls_symbols:
    for i in range(1, len(ldt_timestamps)):
        # Calculating the returns for this timestamp
        f_symprice_today = df_close[s_sym].ix[ldt_timestamps[i]]
        f_symprice_yesterday = df_close[s_sym].ix[ldt_timestamps[i-1]]
        # Event is found if the symbol felt to event_lvl$ on that day 
        if f_symprice_today < event_lvl and f_symprice_yesterday >= event_lvl:
            df_events[s_sym].ix[ldt_timestamps[i]] = 1

print "Done !!" 
