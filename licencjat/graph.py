import matplotlib.pyplot as plt
import numpy as np

num_data = 60;

def col(ar, i):
    return np.array([row[i] for row in ar])

def make_plot(fin, qs_count, fout1, fout2, graph_label = ""):
    with open(fin) as f:
        content = f.readlines()
    # you may also want to remove whitespace characters like `\n` at the end of each line
    data = [(x.strip()).split(' ') for x in content]  
    data = [[float(x) for x in y] for y in data]
    fig1 = plt.figure(figsize= (10, 15))
    for j in range(int(len(data)/qs_count)) : 
        print(j)
        plt.subplot(4, 2, j+1)
        plt.tight_layout()
        #plt.yscale("log")
        xs = col(data[qs_count*j : qs_count*(j+1)], 1)
        lines = [0]*5;
        labels = ["Splay", "Tango", "Drzewo czerwono czarne", "Set", "Statyczne drzewo optymalne"]
        plt.title("Rozmiar struktury" + str(data[qs_count*j][0]))
        for i in range(0, 5): # będzie 5
            ys = col(data[qs_count*j : qs_count*(j+1)], 3 + i * 3)*1000
            ylow = ys - col(data[qs_count*j : qs_count*(j+1)], 2 + i * 3)*1000
            yhigh = col(data[qs_count*j : qs_count*(j+1)], 4 + i * 3)*1000 - ys
            plt.xlabel("Liczba zapytań")
            plt.ylabel("Czas [ms]")
            
            plotted_data = plt.errorbar(xs, ys, yerr=[ylow, yhigh], xerr=None, ecolor=None, elinewidth=None, label = labels[i])
            lines[i] = plotted_data.lines[0]
    fig1.suptitle(graph_label)
    fig1.legend(lines, labels, loc = "lower right");

    plt.savefig(fout1, dpi=None, facecolor='w', edgecolor='w',
            orientation='portrait', papertype=None, format=None,
            transparent=False, bbox_inches=None, pad_inches=0.1,
            frameon=None, metadata=None)
    
    plt.close(fig1)
    fig2 = plt.figure()
    
    main_data = [data[i] for i in np.arange(5, len(data), qs_count)]
    xs = col(main_data, 0)
    
    labels = ["Splay", "Tango", "Drzewo czerwono czarne", "Set", "Statyczne drzewo optymalne"]
    #plt.yscale("log")
    for i in range(0, 5): # będzie 5
        ys = col(main_data, 3 + i * 3)*1000;
        ylow = ys - col(main_data, 2 + i * 3)*1000
        yhigh = col(main_data, 4 + i * 3) *1000 - ys
        plt.xlabel("Rozmiar struktury")
        plt.ylabel("Czas [ms]")
        plt.errorbar(xs, ys, yerr=[ylow, yhigh], xerr=None, ecolor=None, elinewidth=None, label = labels[i])
        
    plt.title(graph_label);
    plt.legend();
    plt.plot()
    plt.savefig(fout2, dpi=None, facecolor='w', edgecolor='w',
            orientation='portrait', papertype=None, format=None,
            transparent=False, bbox_inches=None, pad_inches=0.1,
            frameon=None, metadata=None)  
    plt.close(fig2)
    
make_plot("wyniki/gaus01.res", 6, "wykresy/gaus01", "wykresy/gaus01_main", "Gauss V = 0.1")
make_plot("wyniki/gaus025.res", 6, "wykresy/gaus025", "wykresy/gaus025_main", "Gauss V = 0.1")
make_plot("wyniki/gaus05.res", 6, "wykresy/gaus05", "wykresy/gaus05_main")
make_plot("wyniki/gaus075.res", 6, "wykresy/gaus075", "wykresy/gaus075_main")
make_plot("wyniki/randwalk0.res", 6, "wykresy/randwalk0", "wykresy/randwalk0_main")
make_plot("wyniki/randwalk.res", 6, "wykresy/randwalk", "wykresy/randwalk_main")
make_plot("wyniki/randwalk05.res", 6, "wykresy/randwalk05", "wykresy/randwalk05_main")
make_plot("wyniki/randwalk02.res", 6, "wykresy/randwalk02", "wykresy/randwalk02_main")
make_plot("wyniki/uniform.res", 6, "wykresy/uniform", "wykresy/uniform_main")