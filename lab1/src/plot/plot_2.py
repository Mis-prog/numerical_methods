import matplotlib.pyplot as pl
import pandas as pd

data_equals = pd.read_csv("D:/5sem/numerical/practice/labs/Lab1/cmake-build-debug/task1_plot.txt", sep=" ", names=[1, 2])
data_notequals = pd.read_csv("D:/5sem/numerical/practice/labs/Lab1/cmake-build-debug/task2_plot.txt", sep=" ", names=[1, 2])
data_notequalsnode=pd.read_csv("D:/5sem/numerical/practice/labs/Lab1/cmake-build-debug/notequalsnode.txt", sep=" ", names=[1, 2])

pl.plot(data_equals[1],data_equals[2],linewidth=4,color='green',label="Равномерная сетка")
pl.plot(data_notequals[1],data_notequals[2],linewidth=1,color='black',label="Неравномерная сетка")
pl.scatter(data_notequalsnode[1],data_notequalsnode[2],color='red',label="Узлы")
pl.title("График интерполяции")
pl.xlabel("X")
pl.ylabel("Y")
pl.legend(loc='upper left')
pl.show()