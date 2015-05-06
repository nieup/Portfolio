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
event_lvl = 10.0 # Level of the event 
vol = 100 #Volume to buy / sell 
day_retain = 5 # day to retain stock
cashI = 50000 # Amount of cash Available
cash = 50000 # Amount of cash Available at the begining 

## EVENT REFERENCING :


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


print "Processing events..."

ls_sym = [] # list of Symbols read
dt_date = [] # list of dates 
_vol = [] # Volume in share per transaction

for i in range(1, len(ldt_timestamps)):
    for s_sym in ls_symbols:
        ## buy if you find a 1 in the present day
        if df_events[s_sym].ix[ldt_timestamps[i]] == 1:
            ls_sym = ls_sym + [str(s_sym)] ## Add element to the list
            dt_date = dt_date + [ldt_timestamps[i]]
            _vol = _vol + [vol]
        ## Sell if find a 1 day_retain before ! si i > day_retain :)
        if i > day_retain:
            if df_events[s_sym].ix[ldt_timestamps[i - day_retain]] == 1:
                ls_sym = ls_sym + [str(s_sym)] ## Add element to the list
                dt_date = dt_date + [ldt_timestamps[i]]
                _vol = _vol + [-vol]
        

#get the number of transactions :
count = 0
for elt in ls_sym:
    count = count + 1

# Getting the numpy ndarray of close prices.
na_price = d_data['close'].values

# Counting Variables : 
i = 0
j = 0

# Gets the corresponding price to the symbol, the raw in here refers to the Transaction 
#     the Value to the corrsponding column in the array containing prices :
_sym_to_price = []

for sym_act in ls_sym:
    i = 0 
    for sym_price in ls_symbols:
        if (sym_act == sym_price): _sym_to_price = _sym_to_price + [i]
        i = i + 1

# Initializing variables 
i = 0
k = 0
port = 0 # Price of the protfolio 
argent = [] # value of the portfolio  
argent = argent + [cashI] # Init with available cash 

print "Computing Portfolio..." 

for day in ldt_timestamps: 
        port = 0
        j = 0
        for d_action in dt_date:
            if (day == d_action):
                if ( vol == -_vol[j]):
                    cash = cash - _vol[j] * na_price[i][_sym_to_price[j]]
                    ## print "sold"
                    k = k + 1
                else:
                    cash = cash - _vol[j] * na_price[i][_sym_to_price[j]]
                    ## print "bought"
                    k = k + 1
            j = j + 1
        for l in range(0,k):
            port = port + _vol[l] * na_price[i][_sym_to_price[l]]
        #if port <> 0.0:
        i = i + 1 
        argent = argent + [cash + port]
        
# Should Write the CSV file somehow ...

print "Final cash :"
print argent[i]
print len(argent)

argent = argent[1:]
        
def affiche (dt_jour, argent, ldt_timestamps):
    i = -1
    for day in ldt_timestamps:
            i = i + 1
            if (day == dt_jour):
                    print dt_jour
                    print argent[i]
        
def results(): ### MARKET IS NOT IMPLEMENTED
                #### Checked for what is implemented ... 
        # Compute Total Return of the fund 
      TotRet_Fu = argent[-1] / cashI
      # And of the Market 
      TotRet_M = 0 ###
      
      # Daily Return of fund
      a_DayRet_Fu = []
      buff = cashI

      for elt in argent:
                a_DayRet_Fu = a_DayRet_Fu + [elt / buff]
                buff = copy.copy(elt)
                
      DayRet_Fu = np.mean(a_DayRet_Fu) - 1   
      # And of market
      DayRet_M = 0 ###


      # Std Dev of Fund 
      Std_Fu = round(np.std(a_DayRet_Fu), 11)  
      # Std of Maret
      Std_M = 0 ### 
      
      # compute Sharp of Fund 
      Sh_Fu = round(np.sqrt(252)*DayRet_Fu / Std_Fu, 11)
      # And the one of the market 
      Sh_M = 0 ###
      
      #Print all that in the given dates :
      print "Date Range : from "
      print dt_start
      print " to "
      print dt_end 
      print "\n \n Sharp of Fund :"
      print Sh_Fu
      print "Sharp of $SPX :" 
      print Sh_M
      print "\n Total Return of Fund :"
      print TotRet_Fu
      print "Total Return $SPX :"
      print TotRet_M
      print "\n Std Dev of Fund :" 
      print Std_Fu
      print "Std Dev of $SPX :" 
      print Std_M
      print "\n Avg daily Ret of Fund :" 
      print DayRet_Fu
      print "Avg daily Ret of $SPX :"
      print DayRet_M
      
print "READY !!!" 
