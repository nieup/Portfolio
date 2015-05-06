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

##### BOLLINGER ################

### SETTING VARIABLES :

## TIME : 
# Start and End date 
dt_start = dt.datetime(2010,1,1) ## ENTER DATE 
dt_end = dt.datetime(2010,12,31)## ENTER DATE

# We need closing prices so the timestamp should be hours=16.
dt_timeofday = dt.timedelta(hours=16)

# Get a list of trading days between the start and the end.
ldt_timestamps = du.getNYSEdays(dt_start, dt_end, dt_timeofday)

# Rolling days :
Roll_D = 20

print "Downloading Data" 

dataobj = da.DataAccess('Yahoo')
ls_symbols = dataobj.get_symbols_from_list('sp5002012')
ls_symbols.append('SPY')

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
df_close = d_data['actual_close']

# Time stamps for the event range
ldt_timestamps = df_close.index

s_sym = 'AAPL'
dt_day = dt.datetime(2010,12,23, 16)


#for day in ldt_timestamps:
 #   count = count + 1
  #  if (dt_day == day): inD = count


print df_close[s_sym].ix[dt_day]

def do(s_sym, dt_day):
    count = 0
    inD = 0
    t_price = []
    for day in ldt_timestamps:
        count = count + 1
        if (dt_day == day): inD = count
    
    for i in range(1, Roll_D):
        t_price = t_price + [df_close[s_sym].ix[ldt_timestamps[inD-i]]]

    mean = np.mean(t_price)
    Dev = np.std(t_price)
    Bol = (df_close[s_sym].ix[dt_day] - mean) / Dev
    return Bol, mean, Dev, df_close[s_sym].ix[dt_day]

    
















