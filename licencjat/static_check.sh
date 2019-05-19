#!/bin/bash
#echo "Bash version ${BASH_VERSION}..."
#for (( j = 100; j<=2000; j++ )) #`seq 100 2000`
#do
for i in `seq 1 10000`
do
        ./tango_gen $i $j > testy4/test$i.in
        ./tango_brut < testy4/test$i.in > brut4.out
        ./static_optimal < testy4/test$i.in > testy4/test$i.out
        DIFF=$(diff brut4.out testy4/test$i.out) 
        if [ "$DIFF" != "" ] 
        then 
            echo "Iteracja ma $j wierzcholkow nr: $i"
            echo "Brutal"
            cat brut4.out
            echo "Tree"
            cat testy4/test$i.out
            diff brut4.out testy4/test$i.out
            break
        fi
        echo "$i OK"
done
#done