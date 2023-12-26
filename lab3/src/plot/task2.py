import matplotlib.pyplot as plt
import pandas as pd

def plot_point():
    point = pd.read_csv('D:/5sem/numerical/practice/labs/Lab3/cmake-build-debug/node.txt', sep=' ', names=['X', 'Y'])
    line = pd.read_csv('D:/5sem/numerical/practice/labs/Lab3/cmake-build-debug/line_task2.txt', sep=' ', names=['X', 'Y'])

    plt.plot(line['X'], line['Y'], color='pink',label='Прямая')
    plt.scatter(point['X'], point['Y'],color='dimgray' ,label='Точки')
    plt.grid(True)
    plt.title('Решение методом разложения LU')
    plt.xlabel('Ось X')
    plt.ylabel('Ось Y')
    plt.legend()
    plt.show()

plot_point()
