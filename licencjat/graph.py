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
        plt.subplot(5, 2, j+1)
        plt.tight_layout()
        plt.yscale("log")
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
    plt.yscale("log")
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
    
    
    
def make_ops_plot(fin, fout, graph_label = ""):
    with open(fin) as f:
        content = f.readlines()
    # you may also want to remove whitespace characters like `\n` at the end of each line
    data = [(x.strip()).split(' ') for x in content]  
    data = [[float(x) for x in y] for y in data]
    labels = ["Splay", "Drzewo czerwono czarne", "Set"]
    plt.xlabel("Rozmiar stukrury")
    plt.ylabel("Czas [ms]")
    fig1 = plt.figure();
    xs = col(data, 0)
    for i in range(3) :
        ys = col(data, 2+3*i)*1000;
        ylow = ys - col(data, 1 + 3*i)*1000
        yhigh = col(data, 3 + 3*i)*1000 - ys
        plt.errorbar(xs, ys, yerr=[ylow, yhigh], xerr=None, ecolor=None, elinewidth=None, label = labels[i])
    
    plt.title(graph_label);
    plt.legend();
    plt.plot()
    plt.savefig(fout, dpi=None, facecolor='w', edgecolor='w',
            orientation='portrait', papertype=None, format=None,
            transparent=False, bbox_inches=None, pad_inches=0.1,
            frameon=None, metadata=None)
    plt.close(fig1)

make_plot("wyniki/gaus01.res", 6, "wykresy/gaus01", "wykresy/gaus01_main")
make_plot("wyniki/gaus025.res", 6, "wykresy/gaus025", "wykresy/gaus025_main")
make_plot("wyniki/gaus05.res", 6, "wykresy/gaus05", "wykresy/gaus05_main")
make_plot("wyniki/gaus075.res", 6, "wykresy/gaus075", "wykresy/gaus075_main")
make_plot("wyniki/randwalk5.res", 6, "wykresy/randwalk5", "wykresy/randwalk5_main")
make_plot("wyniki/randwalk25.res", 6, "wykresy/randwalk25", "wykresy/randwalk25_main")
make_plot("wyniki/randwalk50.res", 6, "wykresy/randwalk50", "wykresy/randwalk50_main")
make_plot("wyniki/randwalk75.res", 6, "wykresy/randwalk75", "wykresy/randwalk75_main")
make_plot("wyniki/randwalk100.res", 6, "wykresy/randwalk100", "wykresy/randwalk100_main")
make_plot("wyniki/uniform5.res", 6, "wykresy/uniform5", "wykresy/uniform5_main")
make_plot("wyniki/uniform100.res", 6, "wykresy/uniform100", "wykresy/uniform100_main")
make_plot("wyniki/uniform75.res", 6, "wykresy/uniform75", "wykresy/uniform75_main")
make_plot("wyniki/uniform50.res", 6, "wykresy/uniform50", "wykresy/uniform50_main")
make_plot("wyniki/uniform25.res", 6, "wykresy/uniform25", "wykresy/uniform25_main")
make_ops_plot("wynikiop/inserts.res", "wykresy/inserts")
make_ops_plot("wynikiop/deletes.res", "wykresy/deletes")
