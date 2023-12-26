import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('D:/5sem/numerical/Lab2/cmake-build-debug/task1.txt', sep=',', names=['x', 'y', 'z'],nrows=30)

plt.figure(figsize=(10, 5))
plt.plot(df['x'], df['y'], label='Прямоугольник', linestyle='--', color='blue')
plt.plot(df['x'], df['z'], label='Трапеция', linestyle=':', color='red')

plt.xlabel('i')
plt.ylabel('Квадратура')


plt.legend()

plt.show()
