for i in 4 8 12 16 20 24 28 32 36 64 128 256 512 1024 #`seq 1 25`
do
    for j in `seq 1 10`
    do
        #./cache -n $i -s 21 -t 100 -j 16 >> cache$i.21_16
        ./cache -n 16 -s 16 -t 1000 -j $i >> cache_16_16_$i
    done
done