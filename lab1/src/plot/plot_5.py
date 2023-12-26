import matplotlib.pyplot as pl
import pandas as pd


def plot1():
    data = pd.read_csv("D:/5sem/numerical/practice/labs/Lab1/cmake-build-debug/buap_n_vs_err.txt", sep=" ", names=[1, 2])
    pl1 = pl
    pl1.plot(data[1], data[2],color='red')
    #    pl1.axhline(y=0.0002, color='red', linestyle='--')
    pl1.xlabel("n")
    pl1.ylabel("Tочность")
    pl1.title("Зависимость количества узлов от точности")
    pl1.grid(True)
    pl1.show()

def plot2():
    data = pd.read_csv("D:/5sem/numerical/practice/labs/Lab1/cmake-build-debug/node_task5.txt", sep=" ", names=[1, 2])
    data_line = pd.read_csv("D:/5sem/numerical/practice/labs/Lab1/cmake-build-debug/task1_plot.txt", sep=" ", names=[1, 2])
    pl1 = pl
    pl1.plot(data_line[1],data_line[2])
    pl1.scatter(data[1], data[2],color='red')
    #    pl1.axhline(y=0.0002, color='red', linestyle='--')
    pl1.xlabel("n")
    pl1.ylabel("Tочность")
    pl1.title("Зависимость количества узлов от точности")
    pl1.grid(True)
    pl1.show()
plot2()