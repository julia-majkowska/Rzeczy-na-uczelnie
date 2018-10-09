
function checkMagic1 (a){
    if(a == 0) return false;
    var numbers = a;
    var sum = 0;
    while(numbers > 0){
        var curNum = numbers%10; 
        if(a% curNum != 0) return false; 
        sum += curNum;
        numbers/=10;
    }
    return (a%sum) == 0;

}

var magicList = Array.from({length: 100001}, (x,i) => i).filter(checkMagic1);

function prime(a){
    if(a<2) return false;
    for(i = 2; i*i<=a; i++)
        if(a%i == 0) return false;
    return true;
}

var primeList = Array.from({length: 100001}, (x,i) => i).filter(prime);

//console.log(`2 ${magicList}\n\n 3 ${primeList}`);

function fibrek(n){
    if(n<2) return 1;
    return fibrek(n-1) + fibrek(n-2)
}

function fibit(n){
    var p = 1;
    var pp = 1;
    if(n<2) return 1;
    for(i = 2; i<=n; i++){
        cur = p + pp;
        pp = p;
        p = cur;
    }
    return p
}

function timeBrow(n){
    for(i = 0; i<n; i++){
        var dateStart1 = Date.now()
        fibrek(i + 10);
        var dateEnd1 = Date.now()
        var dateStart2 = Date.now()
        fibit(i + 10);
        var dateEnd2 = Date.now()
        console.log(`|${i} | ${dateEnd1 - dateStart1} | ${dateEnd2 - dateStart2} |`);
    }
}
function timeNode(n){
    for(i = 0; i<n; i++){
        var j = i
        console.time(`timerRek${j}`)
        fibrek(i + 10);
        console.timeEnd(`timerRek${j}`)
        console.time(`timerIt${j}`)
        fibit(i + 10);
        console.timeEnd(`timerIt${j}`)
    }
}
timeNode(20);
timeBrow(20);