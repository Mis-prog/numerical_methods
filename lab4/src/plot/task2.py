import numpy as np
import matplotlib.pyplot as plt

def z(x, y):
    return 1 - np.sin(x + np.log(y)) + x**2 + 12*x

x = np.linspace(-7, -5, 100)
y = np.linspace(2, 6, 100)
X, Y = np.meshgrid(x, y)
Z = z(X, Y)

fig = plt.figure(figsize=(8, 6))
ax = fig.add_subplot(111, projection='3d')
ax.plot_surface(X, Y, Z, rstride=2, cstride=2, cmap='viridis', alpha=0.7)
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('z')

plt.title('z(x, y) = 1 - sin(x + ln(y)) + x^2 + 12*x')
plt.show()

#
# import numpy as np
# import matplotlib.pyplot as plt
#
#
# # Уравнение
# equation = lambda x: 20 * np.log(2 + np.cos(x)) - x - 10
#
# # Приближенные значения корня (начальные значения)
# initial_guesses = np.linspace(-2*np.pi, 2*np.pi, 100)
#
# # Решение уравнения для каждого начального значения
#
#
# # График уравнения
# x_values = np.linspace(-2*np.pi, 2*np.pi, 1000)
# y_values = equation(x_values)
#
# # График решений
# plt.plot(x_values, y_values, label='Уравнение: $20 \ln(2 + \cos(x)) - x - 10$',color='red')
#
# plt.title('График уравнения и его корни')
# plt.xlabel('$x$')
# plt.ylabel('$y$')
# plt.axhline(0, color='black',linewidth=0.5)
# plt.axvline(0, color='black',linewidth=0.5)
# plt.legend()
# plt.grid(color = 'gray', linestyle = '--', linewidth = 0.5)
# plt.show()
