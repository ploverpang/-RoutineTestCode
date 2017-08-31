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

def cvt_img_to_binary(img_name, saved):
    img = cv2.imread(img_name)
    if(img.shape[2] == 3):
        img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    img.tofile(saved)

if __name__ == "__main__":
    if(len(sys.argv) < 2):
        print("not enough param!")
        print_help()
        sys.exit(0)

    if(len(sys.argv) ==3):
        saved_binary = sys.argv[2]
    else:
        saved_binary = "img_binary"
    saved_binary = os.path.normpath(saved_binary)

    input_img = sys.argv[1]
    input_img = os.path.abspath(input_img)
    if(not os.path.exists(input_img)):
        print("input image %s not exist" % input_img)
        sys.exit(0)

    cvt_img_to_binary(input_img, saved_binary)



