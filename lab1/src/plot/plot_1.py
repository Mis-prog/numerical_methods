import matplotlib.pyplot as pl
import pandas as pd


def plot1():
    data = pd.read_csv("D:/5sem/numerical/practice/labs/Lab1/cmake-build-debug/task1_1.txt", sep=" ", names=[1, 2])
    pl1 = pl
    pl1.plot(data[1], data[2],color='red')
#    pl1.axhline(y=0.0002, color='red', linestyle='--')
    pl1.xlabel("Количесто узлов, n")
    pl1.ylabel("Tочность")
    pl1.title("Зависимость точности от количества узлов")
    pl1.grid(True)
    pl1.show()


def plot1_2():
    data2 = pd.read_csv("D:/5sem/numerical/practice/labs/Lab1/cmake-build-debug/task1_2.txt", sep=" ", names=[1, 2])
    pl2 = pl
    pl2.figure(figsize=(10, 5))
    pl2.plot(data2[1], data2[2])
    pl2.xlabel("x")
    pl2.ylabel("Tочность")
    pl2.title("Ошибка приближения")
    pl2.grid(True)
    pl2.show()

plot1();plot1_2();