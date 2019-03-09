#!/bin/sh

for i in `seq 1 100`
do
        ./Dgen $i > testy/test$i.in
        ./Dbrut < testy/test$i.in > brut.out
        ./splay < testy/test$i.in > testy/test$i.out
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