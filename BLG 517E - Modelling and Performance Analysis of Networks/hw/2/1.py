#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import unicode_literals

import numpy as np
import matplotlib.pyplot as plt

plt.rc('font', family='Arial')
plt.rcParams.update({'font.size': 18})

def teo_function(d):
    return 15/d

vecfunc = np.vectorize(teo_function)

d = np.arange(15.0, 100.0, 0.01)
T = vecfunc(d)
plt.plot (d, T, 'bo', d, T, 'k')
plt.ylabel('ρ', fontsize=30)
plt.xlabel('μ', fontsize=30)
plt.title('ρ - μ graph. λ=15', fontsize=30)

plt.show()
