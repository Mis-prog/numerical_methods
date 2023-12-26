import matplotlib.pyplot as pl
import pandas as pd


def plot6_1():
    data = pd.read_csv("D:/5sem/numerical/practice/labs/Lab1/cmake-build-debug/test6.txt", sep=" ", names=[1, 2],nrows=100)
    pl6 = pl
    pl6.plot(data[1], data[2])
    pl6.xlabel("Количество сплайнов")
    pl6.ylabel("Tочность")
    pl6.title("Минимальное количество сплайнов")
    pl6.grid(True)
    pl6.show()
def plot6_2():
    data = pd.read_csv("D:/5sem/numerical/practice/labs/Lab1/cmake-build-debug/task6.txt", sep=" ", names=[1, 2])
    pl6 = pl
    pl6.plot(data[1], data[2])
    pl6.xlabel("x")
    pl6.ylabel("Tочность")
    pl6.title("Ошибка приближения")
    pl6.grid(True)
    pl6.show()

plot6_1();plot6_2();