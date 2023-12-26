import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('D:/5sem/numerical/practice/labs/Lab2/cmake-build-debug/task4.txt', sep=' ', names=['x', 'y'])


plt.plot(df['x'], df['y'])

plt.xlabel('n')
plt.ylabel('Точность')



plt.show()
