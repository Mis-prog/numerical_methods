import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('D:/5sem/numerical/practice/labs/Lab2/cmake-build-debug/task6.txt', sep=' ', names=['x', 'y'])

plt.plot(df['x'], df['y'], color='green')

plt.xlabel('Количество точек', )
plt.ylabel('Точноcть')
plt.grid(True)

plt.show()
