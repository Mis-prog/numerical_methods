import pandas as pd
import matplotlib.pyplot as plt

file_path = "D:/5sem/numerical/practice/labs/Lab3/cmake-build-debug/task3.txt"
point=pd.read_csv("D:/5sem/numerical/practice/labs/Lab3/cmake-build-debug/node_task3.txt",sep=' ', names=['X', 'Y'])
df = pd.read_csv(file_path, delim_whitespace=True, header=None, names=['x'] + [f'y_{i}' for i in range(0, 12)])

plt.figure(figsize=(10, 6))
for i in range(0, 12):
    plt.plot(df['x'], df[f'y_{i}'], label=f'n={i+1}')
plt.scatter(point["X"],point["Y"],color='orange',label="Узлы")

plt.xlabel('x')
plt.ylabel('y')
plt.title('МНК')
plt.legend()
plt.grid(True)
plt.show()
