#!/bin/sh

for i in `seq 1 10000`
do
        ./gen_split_join $i > testy2/test$i.in
        ./brut_split_join < testy2/test$i.in > brut2.out
        ./black_red2 < testy2/test$i.in > testy2/test$i.out
        DIFF=$(diff brut2.out testy2/test$i.out) 
        if [ "$DIFF" != "" ] 
        then 
            echo "Iteracja nr: $i"
            echo "Brutal"
            cat brut2.out
            echo "Tree"
            cat testy2/test$i.out
            break
        fi
        echo "$i OK"
done