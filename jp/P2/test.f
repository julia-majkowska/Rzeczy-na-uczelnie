
(fix ( lambda f : TArrow TNum TNum . 
(lambda x : TNum . 
    (if (eq x 0) 
        then 1
    else (
        if (eq x 1) 
            then 1 
            else (
                (add (f (sub x 2)) (f (sub x 1)))
            )
    ))
))) 10 ;

exception e1 of TNum in 
    ((fix ( lambda f : TArrow TNum TNum . 
    (lambda x : TNum . 
        (if (eq x 0) 
            then (throw e1 0 as TNum) 
        else (
            if (eq x 1) 
                then 1 
                else (
                    (mul x (f (sub x 1)))
                )
        ))
    ))) 8) ;