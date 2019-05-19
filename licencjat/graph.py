import matplotlib.pyplot as plt
import numpy as np

num_data = 60;

def col(ar, i):
    return np.array([row[i] for row in ar])

def make_plot(fin, qs_count, fout1, fout2):
    with open("wyniki/gaus01.res") as f:
        content = f.readlines()
    # you may also want to remove whitespace characters like `\n` at the end of each line
    data = [(x.strip()).split(' ') for x in content]  
    data = [[float(x) for x in y] for y in data]
    fig1 = plt.figure()
    for j in range(int(len(data)/qs_count)) : 
        print(j)
        plt.subplot(3, 2, j+1)
        xs = col(data[qs_count*j : qs_count*(j+1)], 1)
        labels = ["Splay", "Tango", "Drzewo czerwono czarne", "Set"]
        for i in range(0, 4): # będzie 5
            ys = col(data[qs_count*j : qs_count*(j+1)], 3 + i * 3)
            ylow = ys - col(data[qs_count*j : qs_count*(j+1)], 2 + i * 3)
            yhigh = col(data[qs_count*j : qs_count*(j+1)], 4 + i * 3) - ys
            plt.errorbar(xs, ys, yerr=[ylow, yhigh], xerr=None, ecolor=None, elinewidth=None, label = labels[i])
    fig1.legend();

    plt.savefig(fout1, dpi=None, facecolor='w', edgecolor='w',
            orientation='portrait', papertype=None, format=None,
            transparent=False, bbox_inches=None, pad_inches=0.1,
            frameon=None, metadata=None)
    
    plt.close(fig1)
    fig2 = plt.figure()
    
    main_data = [data[i] for i in np.arange(2, len(data), qs_count)]
    xs = col(main_data, 0)
    labels = ["Splay", "Tango", "Drzewo czerwono czarne", "Set"]
    for i in range(0, 4): # będzie 5
        ys = col(main_data, 3 + i * 3)
        ylow = ys - col(main_data, 2 + i * 3)
        yhigh = col(main_data, 4 + i * 3) - ys
        plt.errorbar(xs, ys, yerr=[ylow, yhigh], xerr=None, ecolor=None, elinewidth=None, label = labels[i])
    plt.legend();
    plt.plot()
    plt.savefig(fout2, dpi=None, facecolor='w', edgecolor='w',
            orientation='portrait', papertype=None, format=None,
            transparent=False, bbox_inches=None, pad_inches=0.1,
            frameon=None, metadata=None)  
    plt.close(fig2)
    
make_plot("wyniki/gaus01.res", 6, "wykresy/gaus01", "wykresy/gaus01_main")