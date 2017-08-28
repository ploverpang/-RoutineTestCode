#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import time

def processes(cnt, totalNum):
    percent = min(100, 100.0*cnt/totalNum)
    sys.stdout.write("\r ...%2.3f%% " % percent)
    sys.stdout.flush()

for i in range(10000):
    processes(i, 10000)
    time.sleep(0.01)

