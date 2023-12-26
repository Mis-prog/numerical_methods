import numpy as np
from scipy.integrate import quad

def rectangle_method(func, a, b, n):
    x = np.linspace(a, b, n)
    dx = (b - a) / n
    return np.sum(func(x) * dx)

answer= 0.49906627863414593
epsilon=2*1e-5
def rectangle():
    for i in range(1,1000):
        result_rect = rectangle_method(lambda x: np.exp(-x) * np.sin(x), 0, 2 * np.pi,i)
        if (abs(result_rect-answer)<epsilon):
            print("Метод прямоугольников:", result_rect)
            print("Количество:", i)
            return

rectangle()


