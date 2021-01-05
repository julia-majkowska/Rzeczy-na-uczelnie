exception e1 of TNum in (
    exception e2 of TNum in (
        exception e3 of TNum in (
            try( 
                (lambda x : TNum . (
                    if (eq x 3)
                    then (throw e3 (mul x 3) as TNum)
                    else (
                        if (eq x 2) 
                        then (throw e2 (mul x 2) as TNum)
                        else (throw e1 x as TNum)
                    )
                ))
                2)
            catch {
                e1 x ==> 
                ((fix  x))
                | e2 x ==> 3
                | e3 x ==> (mul 666 x)
            }
        )
    )
);
exception e1 of TNum in (
    exception e2 of TNum in (
        exception e3 of TNum in (
            try( 
                (lambda x : TNum . (
                    if (eq x 3)
                    then (throw e3 (mul x 3) as TNum)
                    else (
                        if (eq x 2) 
                        then (throw e2 (mul x 2) as TNum)
                        else (throw e1 x as TNum)
                    )
                ))
                2)
            catch {
                e1 x ==> 
                ((fix ( lambda f : TArrow TNum TNum . 
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
                    ))) x)
                | e3 x ==> (mul 666 x)
            }
        )
    )
);

exception e1 of TNum in (
    exception e2 of TNum in (
        exception e3 of TNum in (
            (lambda x : TNum . (
                if (eq x 3)
                then (throw e3 (mul x 3) as TNum)
                else (
                    if (eq x 2) 
                    then (throw e2 (mul x 2) as TNum)
                    else (throw e1 x as TNum)
                )
            ))
            3
        )
    )
);

exception bad_argument of TNum in 
    ((fix ( lambda f : TArrow TNum TNum . 
    (lambda x : TNum . 
        (if (eq x 0) 
            then (throw bad_argument 0 as TNum) 
        else (
            if (eq x 1) 
                then 1 
                else (
                    (mul x (f (sub x 1)))
                )
        ))
    ))) 0) ;


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