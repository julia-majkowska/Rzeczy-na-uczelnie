import matplotlib.pyplot as plt
import numpy as np

num_data = 60;

def col(ar, i):
    return np.array([row[i] for row in ar])

def make_plot(fin, qs_count, fout1, fout2, graph_label = "", num_structs = 5):
    with open(fin) as f:
        content = f.readlines()
    # you may also want to remove whitespace characters like `\n` at the end of each line
    data = [(x.strip()).split(' ') for x in content]  
    data = [[float(x) for x in y] for y in data]
    fig1 = plt.figure(figsize= (10, 15))
    for j in range(int(len(data)/qs_count)) : 
        print(j)
        ax = plt.subplot(6, 2, j+1)
        ax.ticklabel_format(axis = 'both', style='sci', scilimits = (-3, 3))
        plt.tight_layout()
        plt.yscale("log")
        #plt.setp(axa.xaxis.get_majorticklabels(), rotation=45)
        xs = col(data[qs_count*j : qs_count*(j+1)], 1)
        lines = [0]*5;
        labels = ["Splay", "Tango", "Drzewo czerwono czarne", "Set", "Statyczne drzewo optymalne"]
        color = ["b", "g", "r", "c", "gold"]
        plt.title("Rozmiar struktury " + str(int(data[qs_count*j][0])))
        for i in range(0, num_structs): # będzie 5
            ys = col(data[qs_count*j : qs_count*(j+1)], 3 + i * 3)*1000
            ylow = ys - col(data[qs_count*j : qs_count*(j+1)], 2 + i * 3)*1000
            yhigh = col(data[qs_count*j : qs_count*(j+1)], 4 + i * 3)*1000 - ys
            plt.xlabel("Liczba zapytań")
            plt.ylabel("Czas [ms]")
            
            plotted_data = plt.errorbar(xs, ys, yerr=[ylow, yhigh], xerr=None, color=color[i], elinewidth=None, label = labels[i])
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
    color = ["b", "g", "r", "c", "gold"]
    plt.yscale("log")
    for i in range(0, num_structs): # będzie 5
        ys = col(main_data, 3 + i * 3)*1000;
        ylow = ys - col(main_data, 2 + i * 3)*1000
        yhigh = col(main_data, 4 + i * 3) *1000 - ys
        plt.xlabel("Rozmiar struktury")
        plt.ylabel("Czas [ms]")
        plt.errorbar(xs, ys, yerr=[ylow, yhigh], xerr=None, color=color[i], elinewidth=None, label = labels[i])
        
    plt.title(graph_label);
    plt.legend();
    plt.plot()
    plt.savefig(fout2, dpi=None, facecolor='w', edgecolor='w',
            orientation='portrait', papertype=None, format=None,
            transparent=False, bbox_inches=None, pad_inches=0.1,
            frameon=None, metadata=None)  
    plt.close(fig2)
    
    
def make_plot2(fin, qs_count, fout1, fout2, graph_label = "", num_structs = 3):
    with open(fin) as f:
        content = f.readlines()
    # you may also want to remove whitespace characters like `\n` at the end of each line
    data = [(x.strip()).split(' ') for x in content]  
    data = [[float(x) for x in y] for y in data]
    fig1 = plt.figure(figsize= (10, 15))
    for j in range(int(len(data)/qs_count)) : 
        print(j)
        ax = plt.subplot(9, 2, j+1)
        ax.ticklabel_format(axis = 'both', style='sci', scilimits = (-3, 3))
        plt.tight_layout()
        plt.yscale("log")
        #plt.setp(axa.xaxis.get_majorticklabels(), rotation=45)
        xs = col(data[qs_count*j : qs_count*(j+1)], 1)
        lines = [0]*5;
        labels = ["Splay", "Drzewo czerwono czarne", "Set"]
        color = ["b","r", "c"]
        #labels = ["Splay", "Tango", "Drzewo czerwono czarne", "Set", "Statyczne drzewo optymalne"]
        plt.title("Rozmiar struktury " + str(int(data[qs_count*j][0])))
        for i in range(0, num_structs): # będzie 5
            ys = col(data[qs_count*j : qs_count*(j+1)], 3 + i * 3)*1000
            ylow = ys - col(data[qs_count*j : qs_count*(j+1)], 2 + i * 3)*1000
            yhigh = col(data[qs_count*j : qs_count*(j+1)], 4 + i * 3)*1000 - ys
            plt.xlabel("Liczba zapytań")
            plt.ylabel("Czas [ms]")
            
            plotted_data = plt.errorbar(xs, ys, yerr=[ylow, yhigh], xerr=None, color=color[i], elinewidth=None, label = labels[i])
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
    labels = ["Splay", "Drzewo czerwono czarne", "Set"]
    color = ["b","r", "c"]
    #labels = ["Splay", "Tango", "Drzewo czerwono czarne", "Set", "Statyczne drzewo optymalne"]
    plt.yscale("log")
    for i in range(0, num_structs): # będzie 5
        ys = col(main_data, 3 + i * 3)*1000;
        ylow = ys - col(main_data, 2 + i * 3)*1000
        yhigh = col(main_data, 4 + i * 3) *1000 - ys
        plt.xlabel("Rozmiar struktury")
        plt.ylabel("Czas [ms]")
        plt.errorbar(xs, ys, yerr=[ylow, yhigh], xerr=None, color=color[i], elinewidth=None, label = labels[i])
        
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
    color = ["b","r", "c"]
    plt.xlabel("Rozmiar stukrury")
    plt.ylabel("Czas [ms]")
    fig1 = plt.figure();
    xs = col(data, 0)
    for i in range(3) :
        ys = col(data, 2+3*i)*1000;
        ylow = ys - col(data, 1 + 3*i)*1000
        yhigh = col(data, 3 + 3*i)*1000 - ys
        plt.errorbar(xs, ys, yerr=[ylow, yhigh], xerr=None, color=color[i], elinewidth=None, label = labels[i])
    
    plt.title(graph_label);
    plt.legend();
    plt.plot()
    plt.savefig(fout, dpi=None, facecolor='w', edgecolor='w',
            orientation='portrait', papertype=None, format=None,
            transparent=False, bbox_inches=None, pad_inches=0.1,
            frameon=None, metadata=None)
    plt.close(fig1)

'''make_plot("wyniki/gaus1.res", 6, "wykresy/gaus1", "wykresy/gaus1_main")
make_plot("wyniki/gaus10.res", 6, "wykresy/gaus10", "wykresy/gaus10_main")
make_plot("wyniki/gaus50.res", 6, "wykresy/gaus50", "wykresy/gaus50_main")
make_plot("wyniki/randwalk1.res", 6, "wykresy/randwalk1", "wykresy/randwalk1_main")
make_plot("wyniki/randwalk10.res", 6, "wykresy/randwalk10", "wykresy/randwalk10_main")
make_plot("wyniki/randwalk50.res", 6, "wykresy/randwalk50", "wykresy/randwalk50_main")
make_plot("wyniki/randwalk100.res", 6, "wykresy/randwalk100", "wykresy/randwalk100_main")
make_plot("wyniki/uniform1.res", 6, "wykresy/uniform1", "wykresy/uniform1_main")
make_plot("wyniki/uniform10.res", 6, "wykresy/uniform10", "wykresy/uniform10_main")
make_plot("wyniki/uniform50.res", 6, "wykresy/uniform50", "wykresy/uniform50_main")
make_plot("wyniki/uniform100.res", 6, "wykresy/uniform100", "wykresy/uniform100_main")
make_ops_plot("wynikiop/inserts.res", "wykresy/inserts")
make_ops_plot("wynikiop/deletes.res", "wykresy/deletes")'''
make_plot2("wyniki3/gaus001.res", 3, "wykresy/gaus001", "wykresy/gaus001_main")
make_plot2("wyniki3/gaus1.res", 3, "wykresy/gaus1", "wykresy/gaus1_main")
make_plot2("wyniki3/gaus10.res", 3, "wykresy/gaus10", "wykresy/gaus10_main")
make_plot2("wyniki3/gaus50.res", 3, "wykresy/gaus50", "wykresy/gaus50_main")
make_plot2("wyniki3/randwalk001.res", 3, "wykresy/randwalk001", "wykresy/randwalk001_main")
make_plot2("wyniki3/randwalk1.res", 3, "wykresy/randwalk1", "wykresy/randwalk1_main")
make_plot2("wyniki3/randwalk10.res", 3, "wykresy/randwalk10", "wykresy/randwalk10_main")
make_plot2("wyniki3/randwalk50.res", 3, "wykresy/randwalk50", "wykresy/randwalk50_main")
make_plot2("wyniki3/randwalk100.res", 3, "wykresy/randwalk100", "wykresy/randwalk100_main")
make_plot2("wyniki3/uniform001.res", 3, "wykresy/uniform001", "wykresy/uniform001_main")
make_plot2("wyniki3/uniform1.res", 3, "wykresy/uniform1", "wykresy/uniform1_main")
make_plot2("wyniki3/uniform10.res", 3, "wykresy/uniform10", "wykresy/uniform10_main")
make_plot2("wyniki3/uniform50.res", 3, "wykresy/uniform50", "wykresy/uniform50_main")
make_plot2("wyniki3/uniform100.res", 3, "wykresy/uniform100", "wykresy/uniform100_main")