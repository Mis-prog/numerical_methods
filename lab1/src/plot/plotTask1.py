import matplotlib.pyplot as pl
import pandas as pd


def plot1():
    data = pd.read_csv("D:/5sem/numerical/Lab1/cmake-build-debug/task1.txt", sep=" ", names=[1, 2])
    pl1 = pl
    pl1.plot(data[1], data[2])
    pl1.axhline(y=0.0002, color='red', linestyle='--')
    pl1.xlabel("Количесто узлов, n")
    pl1.ylabel("Tочность")
    pl1.title("Зависимость Δn")
    pl1.grid(True)
    pl1.show()


def plot1_2():
    data2 = pd.read_csv("D:/5sem/numerical/Lab1/cmake-build-debug/task1_2.txt", sep=" ", names=[1, 2])
    pl2 = pl
    pl2.figure(figsize=(10, 5))
    pl2.plot(data2[1], data2[2])
    pl2.xlabel("x")
    pl2.ylabel("Tочность")
    pl2.title("Ошибка приближения")
    pl2.grid(True)
    pl2.show()


def plot2():
    data3 = pd.read_csv("D:/5sem/numerical/Lab1/cmake-build-debug/task2.txt", sep=" ", names=[1, 2])
    pl3 = pl
    pl3.figure(figsize=(10, 5))
    pl3.plot(data3[1], data3[2])
    pl3.xlabel("x")
    pl3.ylabel("Tочность")
    pl3.title("Ошибка приближения")
    pl3.grid(True)
    pl3.show()


def check_accur():
    data2 = pd.read_csv("D:/5sem/numerical/Lab1/cmake-build-debug/task1_2.txt", sep=" ", names=[1, 2])
    data3 = pd.read_csv("D:/5sem/numerical/Lab1/cmake-build-debug/task2.txt", sep=" ", names=[1, 2])
    pl.figure(figsize=(10, 5))
    pl.subplot(121)
    pl.plot(data2[1], data2[2])
    pl.subplot(122)
    pl.plot(data3[1], data3[2])
    pl.show()

def plot3():
    data1 = pd.read_csv("D:/5sem/numerical/Lab1/cmake-build-debug/task1_2.txt", sep=" ", names=[1, 2])
    data2 = pd.read_csv("D:/5sem/numerical/Lab1/cmake-build-debug/task3.txt", sep=" ", names=[1, 2])
    pl.figure(figsize=(11, 5))
    pl.subplot(121)
    pl.plot(data1[1], data1[2])
    pl.subplot(122)
    pl.plot(data2[1], data2[2])
    pl.show()


def plot6():
    data = pd.read_csv("D:/5sem/numerical/Lab1/cmake-build-debug/task6.txt", sep=" ", names=[1, 2])
    pl6 = pl
    pl6.plot(data[1], data[2])
    pl6.xlabel("x")
    pl6.ylabel("Tочность")
    pl6.title("Ошибка приближения")
    pl6.grid(True)
    pl6.show()

plot3()