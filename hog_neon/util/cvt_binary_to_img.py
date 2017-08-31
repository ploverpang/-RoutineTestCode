#!/usr/bin/env python
# -*- coding: utf-8 -*-
import os
import sys
import cv2
import numpy as np

"""
File: cvt_img_to_binary_file.py
Author: PangBo <bo.pang@metoak.com> <ploverpang@gmail.com>
Email: yourname@email.com
Github: https://github.com/yourname
Description:
"""

def print_help():
    pass

def cvt_binary_to_img(binary_name, image_size, data_type, saved):
    img = np.fromfile(binary_name, np.uint8)
    cv2.normalize(img, img, 0, 255, cv2.NORM_MINMAX)
    img = img.reshape(image_size)
    cv2.imwrite(saved, img)

if __name__ == "__main__":
    if(len(sys.argv) < 2):
        print("not enough param!")
        print_help()
        sys.exit(0)

    binary_name = sys.argv[1]
    binary_name = os.path.abspath(binary_name)
    if(not os.path.exists(binary_name)):
        print("input image %s not exist" % binary_name)
        sys.exit(0)

    image_size = (int(sys.argv[2]),int(sys.argv[3]),int(sys.argv[4]))
    print image_size
    if(sys.argv[5] == "u16"):
       data_type = np.uint16
    elif(sys.argv[5] == "u8"):
       data_type = np.uint8
    elif(sys.argv[5] == "i8"):
       data_type = np.int8
    elif(sys.argv[5] == "i16"):
       data_type = np.int16
    elif(sys.argv[5] == "f32"):
       data_type = np.float32
    else:
        print ("not support this type now")
        sys.exit(0)

    if(len(sys.argv) ==7):
        saved_img = sys.argv[6]
    else:
        saved_img = "saved_img.png"

    saved_img = os.path.normpath(saved_img)
    cvt_binary_to_img(binary_name, image_size, data_type, saved_img)



