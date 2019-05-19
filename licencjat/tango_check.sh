#!/bin/bash
#echo "Bash version ${BASH_VERSION}..."
#for (( j = 100; j<=2000; j++ )) #`seq 100 2000`
#do
for i in `seq 1 10000`
do
        ./tango_gen $i $j > testy3/test$i.in
        ./tango_brut < testy3/test$i.in > brut3.out
        ./tango < testy3/test$i.in > testy3/test$i.out
        DIFF=$(diff brut3.out testy3/test$i.out) 
        if [ "$DIFF" != "" ] 
        then 
            echo "Iteracja ma $j wierzcholkow nr: $i"
            echo "Brutal"
            cat brut3.out
            echo "Tree"
            cat testy3/test$i.out
            diff brut3.out testy3/test$i.out
            break
        fi
        echo "$i OK"
done
#done