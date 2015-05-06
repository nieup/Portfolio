## Cédric HUMBERT HOMEWORK 1
## Computational investing 

# QSTK Imports
import QSTK.qstkutil.qsdateutil as du
import QSTK.qstkutil.tsutil as tsu
import QSTK.qstkutil.DataAccess as da

# Third Party Imports
import datetime as dt
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np



def simulate(dt_start, dt_end, ls_symbols, Allo):
    
    ## Implement variables
    dt_timeofday = dt.timedelta(hours=16)
    # Get a list of trading days between the start and the end.
    ldt_timestamps = du.getNYSEdays(dt_start, dt_end, dt_timeofday)
    # Creating an object of the dataaccess class with Yahoo as the source.
    c_dataobj = da.DataAccess('Yahoo')
    # Keys to be read from the data, it is good to read everything in one go.
    ls_keys = ['close', 'volume']
    # Reading the data, now d_data is a dictionary with the keys above.
    # Timestamps and symbols are the ones that were specified before.
    ldf_data = c_dataobj.get_data(ldt_timestamps, ls_symbols, ls_keys)
    d_data = dict(zip(ls_keys, ldf_data))
    # Getting the numpy ndarray of close prices.
    na_price = d_data['close'].values


    #MAKE STD DEV : 
    na_buffer = na_price.copy()
    na_daily_ret = na_price[:,1].copy()
    na_buffer[0,:] = na_price[0,:]/na_price[0,:]
    for i in range(1,len(ldt_timestamps)):
        na_buffer[i] = na_buffer[i,:]/na_price[i-1,:]
    for i in range(0, len(ldt_timestamps)):
        na_daily_ret[i] = sum(na_buffer[i] * Allo)
    Std_Dev = np.std(na_daily_ret)
    

    #MAKE FINAL RETURN : 
    na_final_normalized_price = na_price[-1,:]/na_price[0,:]
    Final_Return = round(sum(na_final_normalized_price * Allo), 11)

    #MAKE AVG DAILY RETURN :
    Avg_Daily_Ret = np.mean(na_daily_ret - 1) 

    #MAKE SHARPE RATIO :
    Sharpe_Ratio = round(np.sqrt(252) * (Avg_Daily_Ret) / Std_Dev, 11) 
    
    return Std_Dev, Avg_Daily_Ret, Sharpe_Ratio, Final_Return

def optimizer(dt_start, dt_end, ls_symbols):
    
    ## Implement variables
    dt_timeofday = dt.timedelta(hours=16)
    # Get a list of trading days between the start and the end.
    ldt_timestamps = du.getNYSEdays(dt_start, dt_end, dt_timeofday)
    # Creating an object of the dataaccess class with Yahoo as the source.
    c_dataobj = da.DataAccess('Yahoo')
    # Keys to be read from the data, it is good to read everything in one go.
    ls_keys = ['close', 'volume']
    # Reading the data, now d_data is a dictionary with the keys above.
    # Timestamps and symbols are the ones that were specified before.
    ldf_data = c_dataobj.get_data(ldt_timestamps, ls_symbols, ls_keys)
    d_data = dict(zip(ls_keys, ldf_data))
    # Getting the numpy ndarray of close prices.
    na_price = d_data['close'].values
    mem = 0
    Best_Sharpe = 0
    for j in range(1, 9100):
        if (ret_allo(j) != [0,0,0,0]):
            Allo = ret_allo(j)
            #MAKE STD DEV : 
            na_buffer = na_price.copy()
            na_daily_ret = na_price[:,1].copy()
            na_buffer[0,:] = na_price[0,:]/na_price[0,:]
            for i in range(1,len(ldt_timestamps)):
                na_buffer[i] = na_buffer[i,:]/na_price[i-1,:]
            for i in range(0, len(ldt_timestamps)):
                na_daily_ret[i] = sum(na_buffer[i] * Allo)
            Std_Dev = round(np.std(na_daily_ret), 11) 
            #MAKE FINAL RETURN : 
            na_final_normalized_price = na_price[-1,:]/na_price[0,:]
            Final_Return = round(sum(na_final_normalized_price * Allo), 11)

            #MAKE AVG DAILY RETURN :
            Avg_Daily_Ret = round(np.mean(na_daily_ret) - 1, 11) 

            #MAKE SHARPE RATIO :
            Sharpe_Ratio = round(np.sqrt(252)*Avg_Daily_Ret / Std_Dev, 11)
            
            if (Best_Sharpe < Sharpe_Ratio):
                mem = j
                Best_Sharpe = Sharpe_Ratio
                

    Allo = ret_allo(mem)
    #MAKE STD DEV : 
    na_buffer = na_price.copy()
    na_daily_ret = na_price[:,1].copy()
    na_buffer[0,:] = na_price[0,:]/na_price[0,:]
    for i in range(1,len(ldt_timestamps)):
        na_buffer[i] = na_buffer[i,:]/na_price[i-1,:]
    for i in range(0, len(ldt_timestamps)):
        na_daily_ret[i] = sum(na_buffer[i] * Allo)
    Std_Dev = round(np.std(na_daily_ret), 11) 
    

    #MAKE FINAL RETURN : 
    na_final_normalized_price = na_price[-1,:]/na_price[0,:]
    Final_Return = round(sum(na_final_normalized_price * Allo), 11)

    #MAKE AVG DAILY RETURN :
    Avg_Daily_Ret = round(np.mean(na_daily_ret) - 1, 11) 

    #MAKE SHARPE RATIO :
    Sharpe_Ratio = round(np.sqrt(252)*Avg_Daily_Ret / Std_Dev, 11) 
    
    return Std_Dev, Avg_Daily_Ret, Sharpe_Ratio, Final_Return, Allo 
    
def ret_allo(index):
    k = round((index%10)*0.1,1)
    l = round(((index/10)%10)*0.1, 1)
    m = round(((index/100)%10)*0.1,1)
    n = round(((index/1000)%10)*0.1,1) 
    allo = [k, l, m, n]
    if (sum(allo) != 1): allo = [0,0,0,0]
    if (index == 1): allo = [0,0,0,1]
    if (index == 2): allo = [0,0,1,0]
    if (index == 3): allo = [0,1,0,0]
    if (index == 4): allo = [1,0,0,0]
    return allo
