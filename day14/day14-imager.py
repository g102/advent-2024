import os
import cv2 as cv
import numpy as np

files = os.listdir("./out-maps")
for file in files:
    with open(f"./out-maps/{file}", "r") as file_in:
        text = file_in.read().splitlines()
    m = np.array([[int(_ == "X") * 255 for _ in line] for line in text])
    m = m.astype(np.uint8)
    newname = file.replace(".txt", ".bmp")
    newfile = f"./out-imgs/{newname}"
    cv.imwrite(newfile, m)
