import matplotlib.pyplot as plt
import numpy as np

dates = []
macd_values = []
signal_values = []

with open("C:/Users/Hubert/Desktop/Projekty PP/MACD/MACD_Signal_Values.txt") as f:
    for line in f:
        values = line.split()
        if "nan" in values:
            continue
        date, macd_value, signal_value = values
        dates.append(date)
        macd_values.append(float(macd_value))
        signal_values.append(float(signal_value))


if not dates or not macd_values or not signal_values:
    print("No valid data found in file.")
    exit()


fig, ax = plt.subplots()
ax.plot(dates, macd_values, label="MACD")
ax.plot(dates, signal_values, label="Signal")
ax.set_xlabel("Date")
ax.set_ylabel("Value")
ax.set_title("MACD and Signal Values")
ax.legend()


num_ticks = 100  
tick_step = len(dates) // num_ticks
if tick_step < 1:
    tick_step = 1
tick_indices = np.arange(0, len(dates), tick_step)
ax.set_xticks(tick_indices)
ax.set_xticklabels([dates[i] for i in tick_indices], rotation=45, ha='right')


plt.show()