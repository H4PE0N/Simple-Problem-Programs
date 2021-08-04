
import tkinter

window = tkinter.Tk()

canvas = tkinter.Canvas(window, width=800, height=800)

noise = [
    [0.00, 0.02, 0.03, 0.03, 0.02, 0.00, -0.09, -0.14],
    [0.28, 0.23, 0.15, 0.04, -0.10, -0.27, -0.32, -0.33],
    [0.42, 0.35, 0.24, 0.07, -0.14, -0.41, -0.41, -0.40],
    [0.42, 0.39, 0.29, 0.13, -0.10, -0.41, -0.39, -0.36],
    [0.28, 0.35, 0.32, 0.21, 0.01, -0.27, -0.24, -0.21],
    [0.00, 0.21, 0.32, 0.32, 0.21, 0.00, 0.04, 0.06],
    [-0.27, -0.01, 0.17, 0.27, 0.29, 0.22, 0.29, 0.31],
    [-0.40, -0.14, 0.06, 0.21, 0.30, 0.34, 0.43, 0.47]
]

for hIndex in range(0, 7, 1):
    for wIndex in range(0, 7, 1):
        height = (hIndex * 100); width = (wIndex * 100)
        cValue = noise[hIndex][wIndex] + 1.0 # 0 - 2
        color = "gray%d" % (cValue * 44 + 1)
        canvas.create_rectangle(width, height, width + 100, height + 100, fill=color)

canvas.pack()

window.mainloop()
