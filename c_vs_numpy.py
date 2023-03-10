import numpy as np
import random
import timeit
import pandas as pd
from matplotlib import pyplot as plt
import std

if __name__ == '__main__':

    lens = range(1000, 20000, 1000)
    lp_time = []
    py_time = []
    np_time = []
    c_time = []

    for l in lens:
        rands = [random.random() for _ in range(0, 1)]
        numpy_rands = np.array(rands)
        np_time = np.append(np_time, timeit.timeit(lambda: np.std(numpy_rands), number=1000))
        c_time = np.append(c_time, timeit.timeit(lambda: std.standard_dev(rands), number=1000))

    data = np.array( [np.transpose(np.time), np.transpose(c_time)] )

    df = pd.DataFrame(data.transpose(), index=lens, columns=['Numpy', 'C++'])
    plt.figure()
    df.plot()
    plt.legend(loc='best')
    plt.ylegend('time (s)')
    plt.xlabel('Number of elements')
    plt.title('1k runs of standard deviation')
    plt.savefig('numpy_vs_c.png')