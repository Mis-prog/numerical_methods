import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('D:/5sem/numerical/Lab2/cmake-build-debug/task2.txt', sep=',', names=['x', 'y'],nrows=30)

plt.figure(figsize=(10, 5))
plt.plot(df['x'], df['y'], label='Парабола', linestyle='--', color='blue')

plt.xlabel('n')
plt.ylabel('Точность')


plt.legend()

plt.show()
