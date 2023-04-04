import matplotlib.pyplot as plt

with open('../OutputFiles/Etherium_Values.txt', 'r') as f:
    data = [float(line.strip()) for line in f]

x_values = list(range(1, 1001))

plt.plot(x_values, data)
plt.xlabel('Day')
plt.ylabel('Value')
plt.title('Etherium Prices')
plt.show()