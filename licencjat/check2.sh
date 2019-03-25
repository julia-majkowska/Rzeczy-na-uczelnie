#!/bin/sh

for i in `seq 1 100`
do
        ./gen_split_join $i > testy2/test$i.in
        ./brut_split_join < testy2/test$i.in > brut.out
        ./black_red2 < testy2/test$i.in > testy2/test$i.out
        DIFF=$(diff brut.out testy/test$i.out) 
        if [ "$DIFF" != "" ] 
        then 
            echo "Iteracja nr: $i"
            cat brut.out
            cat testy/test$i.out
            break
        fi
        echo "$i OK"
done