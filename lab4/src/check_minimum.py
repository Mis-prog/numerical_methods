from scipy.optimize import minimize
import numpy as np

# Определение функции
def objective(x):
    return 1 - np.sin(x[0] + np.log(x[1])) + x[0]**2 + 12 * x[0]

# Начальная догадка
initial_guess = [-7, 2]

# Оптимизация функции
result = minimize(objective, initial_guess, method='Nelder-Mead')

# Вывод результата
print("Минимум функции:", result.fun)
print("Аргументы минимума:", result.x)
