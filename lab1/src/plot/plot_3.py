import matplotlib.pyplot as pl
import pandas as pd


def plot1():
    data = pd.read_csv("D:/5sem/numerical/practice/labs/Lab1/cmake-build-debug/task3.txt", sep=" ", names=[1, 2])
    pl1 = pl
    pl1.plot(data[1], data[2],color='red')
    #    pl1.axhline(y=0.0002, color='red', linestyle='--')
    pl1.xlabel("x")
    pl1.ylabel("Tочность")
    pl1.title("Точность на n=10")
    pl1.grid(True)
    pl1.show()

plot1();
