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


na_data = pd.read_csv('orders2.csv',header=None,keep_default_na=True,names=['Year', 'Month', 'Day', 'sym', 'action', 'vol','NaN'],delimiter=',')
date = zip(na_data['Year'],na_data['Month'],na_data['Day'])

cash = 1000000

ls_sym = []
for elt in na_data['sym']:
	ls_sym = ls_sym + [str(elt).replace(' ','')]

ls_symbols = list(set(ls_sym))

#get the count of actions :
count = 0
for elt in na_data['sym']:
    count = count + 1

dt_date = []
for j in range(0,count):
    dt_date = dt_date + [dt.datetime(int(date[j][0]), int(date[j][1]), int(date[j][2]), 16)]

_vol = []
for elt in na_data['vol']:
    _vol = _vol + [elt]

_act = []
for elt in na_data['action']:
    _act = _act + [str(elt).replace(' ','')]



# Start and End date of the charts
dt_start = dt.datetime(int(date[0][0]), int(date[0][1]), int(date[0][2]))
dt_end = dt.datetime(int(date[count-1][0]), int(date[count-1][1]), int(date[count-1][2]+1))

    # We need closing prices so the timestamp should be hours=16.
dt_timeofday = dt.timedelta(hours=16)

    # Get a list of trading days between the start and the end.
ldt_timestamps = du.getNYSEdays(dt_start, dt_end, dt_timeofday)

    # Creating an object of the dataaccess class with Yahoo as the source.
c_dataobj = da.DataAccess('Yahoo')

    # Keys to be read from the data, it is good to read everything in one go.
ls_keys = ['open', 'high', 'low', 'close', 'volume', 'actual_close']

    # Reading the data, now d_data is a dictionary with the keys above.
    # Timestamps and symbols are the ones that were specified before.
ldf_data = c_dataobj.get_data(ldt_timestamps, ls_symbols, ls_keys)
d_data = dict(zip(ls_keys, ldf_data))

   # Filling the data for NAN
for s_key in ls_keys:
    d_data[s_key] = d_data[s_key].fillna(method='ffill')
    d_data[s_key] = d_data[s_key].fillna(method='bfill')
    d_data[s_key] = d_data[s_key].fillna(1.0)

# Getting the numpy ndarray of close prices.
na_price = d_data['close'].values

cash = 1000000

i = 0
j = 0
_sym_to_price = []

for sym_act in ls_sym:
    i = 0 
    for sym_price in ls_symbols:
        if (sym_act == sym_price): _sym_to_price = _sym_to_price + [i]
        i = i +1

i = 0
port = 0
k = 0
argent = []
argent = argent + [cash]

for day in ldt_timestamps:
    port = 0
    j = 0
    for d_action in dt_date:            
        if (day == d_action):
            if (_act[j] == 'Sell'):
                cash = cash + _vol[j] * na_price[i][_sym_to_price[j]]
                print "sold"
                k = k + 1
            else:
                cash = cash - _vol[j] * na_price[i][_sym_to_price[j]]
                print "bought"
                k = k + 1
        j = j + 1
    for l in range(0,k):
        if (_act[l] == 'Sell'):
            port = port - _vol[l] * na_price[i][_sym_to_price[l]]
        else:
            port = port + _vol[l] * na_price[i][_sym_to_price[l]]
    #print "Total :"
    #print argent[i]
    #print "----------------------"
    i = i + 1
    #print "day :"
    #print day
    #print "cash :"
    #print cash
    #print " port :" 
    #print port
    argent = argent + [cash + port]
    
print "Total :"
print argent[i]
        
def affiche (dt_jour, argent, ldt_timestamps):
    i = 1
    for day in ldt_timestamps:
        if (day == dt_jour):
            print dt_jour
            print argent[i]
        i = i + 1 

    
