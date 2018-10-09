for i in `seq 1 10`
do
            #./bsearch -S 0x5bab3de5da7882ff -n 23 -t 24 -v 0 >> bin0_23_24_test1
            #./bsearch -S 0x5bab3de5da7882ff -n 23 -t 24 -v 1 >> bin1_23_24_test1
            
            #./bsearch -S 0x27841496381ef019 -n 23 -t 24 -v 0 >> bin0_23_24_test2
            #./bsearch -S 0x27841496381ef019 -n 23 -t 24 -v 1 >> bin1_23_24_test2
            
            #./bsearch -S 0x5bab3de5da7882ff -n 20 -t 24 -v 0 >> bin0_20_24_test1
            #./bsearch -S 0x5bab3de5da7882ff -n 20 -t 24 -v 1 >> bin1_20_24_test1
            
            #./bsearch -S 0x27841496381ef019 -n 20 -t 24 -v 0 >> bin0_20_24_test2
            #./bsearch -S 0x27841496381ef019 -n 20 -t 24 -v 1 >> bin1_20_24_test2
            
            ./bsearch -S 0x5bab3de5da7882ff -n 15 -t 24 -v 0 >> bin0_15_24_test1
            ./bsearch -S 0x5bab3de5da7882ff -n 15 -t 24 -v 1 >> bin1_15_24_test1
            
            ./bsearch -S 0x27841496381ef019 -n 15 -t 24 -v 0 >> bin0_15_24_test2
            ./bsearch -S 0x27841496381ef019 -n 15 -t 24 -v 1 >> bin1_15_24_test2
            
            #./matmult -n 1024 -v 0 >> mult0_1024_test1
            #./matmult -n 1024 -v 1 >> mult1_1024_test1
            #./matmult -n 1024 -v 2 >> mult2_1024_test1
            #./matmult -n 1024 -v 3 >> mult3_1024_test5 #dorzuce potem tylko do mult 3 inne blocki
            
            #./matmult -n 128 -v 0 >> mult0_128_test1
            #./matmult -n 128 -v 1 >> mult1_128_test1
            #./matmult -n 128 -v 2 >> mult2_128_test1
            #./matmult -n 128 -v 3 >> mult3_128_test1
            
            #./matmult -n 4096 -v 0 >> mult0_4096_test1
            #./matmult -n 4096 -v 1 >> mult1_4096_test1
            #./matmult -n 4096 -v 2 >> mult2_4096_test1
            #./matmult -n 4096 -v 3 >> mult3_4096_test1
            
            #./transpose -n 4096 -v 0 >> trans0_4096_test5  potem inne kafelki
            
            #./transpose -n 64 -v 0 >> trans0_64_test1
                
            #./transpose -n 256 -v 0 >> trans0_256_test1
            
            
            #./transpose -n 8192 -v 0 >> trans0_8192_test5
            #./transpose -n 8192 -v 1 >> trans1_8192_test5
            
            #./transpose -n 2048 -v 0 >> trans0_2048_test5
            #./transpose -n 2048 -v 1 >> trans1_2048_test5
            
            #./randwalk -S 0xea3495cc76b34acc -n 7 -s 16 -t 14 -v 0 >> rand0_7_16_14_test1
            #./randwalk -S 0xea3495cc76b34acc -n 7 -s 16 -t 14 -v 1 >> rand1_7_16_14_test1
            
            #./randwalk -S 0xea3495cc76b34acc -n 8 -s 16 -t 14 -v 0 >> rand0_8_16_14_test1
            #./randwalk -S 0xea3495cc76b34acc -n 8 -s 16 -t 14 -v 1 >> rand1_8_16_14_test1
            
            #./randwalk -S 0xea3495cc76b34acc -n 9 -s 16 -t 14 -v 0 >> rand0_9_16_14_test1
            #./randwalk -S 0xea3495cc76b34acc -n 9 -s 16 -t 14 -v 1 >> rand1_9_16_14_test1
            
            #./randwalk -S 0xea3495cc76b34acc -n 10 -s 16 -t 14 -v 0 >> rand0_10_16_14_test1
            #./randwalk -S 0xea3495cc76b34acc -n 10 -s 16 -t 14 -v 1 >> rand1_10_16_14_test1
            
            #./randwalk -S 0xea3495cc76b34acc -n 15 -s 16 -t 14 -v 0 >> rand0_15_16_14_test1
            #./randwalk -S 0xea3495cc76b34acc -n 20 -s 16 -t 14 -v 0 >> rand00_20_16_14_test1
         
         
         
         
done