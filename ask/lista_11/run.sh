for i in `seq 1 50`
do
        ./bsearch -n 23 -t 24 -v 0 >> outbin1
        ./bsearch -n 23 -t 24 -v 1 >> outbin2
done