//zadanie1
var Person = {
  init: function(name) {
    this.name = name;
  },

  introduce: function() {
    console.log(this.name ? this.name : "I don't have a name :(");
  }
};

var p = Object.create(Person);
p.init("Kasia");
p.lastName = "Nowak";
p.social = 1234567;
p.goodName = function() {
  return this.name[0] == this.name[0].toUpperCase();
};
Object.defineProperty(p, "pesel", {
  get: function() {
    return this.social;
  },
  set: function(newVal) {
    this.social = newVal;
  }
});
p.introduce();
p.pesel = 987654321;
console.log(p.pesel);

//zadanie2

function fibrek(n) {
  if (n < 2) return 1;
  return fibrek(n - 1) + fibrek(n - 2);
}

function fibit(n) {
  var p = 1;
  var pp = 1;
  if (n < 2) return 1;
  for (var i = 2; i <= n; i++) {
    cur = p + pp;
    pp = p;
    p = cur;
  }
  return p;
}

function fibmemo() {
  var cache = {};

  var memorec = function(n) {
    if (n <= 1) return 1;
    if (n in cache) {
      return cache[n];
    } else {
      var res = memorec(n - 1) + memorec(n - 2);
      cache[n] = res;
      return res;
    }
  };
}

function timeBrow(n) {
  for (var i = 0; i < n; i++) {
    var dateStart1 = Date.now();
    fibrek(i + 10);
    var dateEnd1 = Date.now();
    var dateStart2 = Date.now();
    fibit(i + 10);
    var dateEnd2 = Date.now();
    console.log(
      `|${i} | ${dateEnd1 - dateStart1} | ${dateEnd2 - dateStart2} |`
    );
  }
}
function timeNode(n) {
  for (var i = 0; i < n; i += 1) {
    var j = i;
    console.log(j);
    console.time(`timerRek${j}`);
    fibrek(j);
    console.timeEnd(`timerRek${j}`);
    console.time(`timerIt${j}`);
    fibit(j);
    console.timeEnd(`timerIt${j}`);
    console.time(`timerMemo${j}`);
    fibmemo(j);
    console.timeEnd(`timerMemo${j}`);
  }
}
//timeNode(40);

//zadanie3
function forEach(a, f) {
  for (i in a) {
    f(i);
  }
}
function map(a, f) {
  res = [];
  for (i in a) {
    res.push(f(a[i]));
  }
  return res;
}
function filter(a, f) {
  res = [];
  for (i in a) {
    if (f(a[i])) res.push(a[i]);
  }
  return res;
}
var a = [1, 2, 3, 4];
forEach(a, _ => {
  console.log(_);
});
// [1,2,3,4]
var resf = filter(a, _ => _ < 3);
// [1,2]
var resm = map(a, _ => _ * 2);

console.log(resf, resm);

//zadanie4
function createFs(n) {
  // tworzy tablicę n funkcji
  var fs = []; // i-ta funkcja z tablicy ma zwrócić i
  var id = function(a) {
    return a;
  };
  for (var i = 0; i < n; i++) {
    fs[i] = function() {
      var res = function() {
        return i;
      };
      return res();
    };
  }
  return fs;
}
var myfs = createFs(10);
console.log(myfs[0]()); // zerowa funkcja miała zwrócić 0
console.log(myfs[2]()); // druga miała zwrócić 2
console.log(myfs[7]());
// 10 10 10

//zadanie5

function sum() {
  var i;
  var sum = 0;
  for (i = 0; i < arguments.length; i++) {
    sum += arguments[i];
  }
  return sum;
}
console.log(sum(1, 2, 3));
// 6
console.log(sum(1, 2, 3, 4, 5));
// 15

//zadanie6

function createGenerator(len) {
  var _state = 0;
  return {
    next: function() {
      return {
        value: _state,
        done: _state++ >= len
      };
    }
  };
}
var foo = {
  [Symbol.iterator]: () => createGenerator(8)
};
var foo1 = {
  [Symbol.iterator]: () => createGenerator(3)
};
for (var f of foo) console.log(f);

//zadanie7
function fib() {
  var _last = 1;
  var _secondToLast = 0;
  return {
    next: function() {
      var help = _last;
      _last += _secondToLast;
      _secondToLast = help;
      return {
        value: _last,
        done: false
      };
    }
  };
}
function* fib1() {
  var last = 1;
  var secondToLast = 0;
  while (true) {
    yield last;
    var help = last;
    last += secondToLast;
    secondToLast = help;
  }
}

/*var _it = fib();
for (var _result; (_result = _it.next()), !_result.done; ) {
  console.log(_result.value);
}

for (var i of fib1()) {
  console.log(i);
}*/
//Zadanie8

function* take(it, top) {
  for (var j = 0; j < top; j++) yield it.next();
}
// zwróć dokładnie 10 wartości z potencjalnie
// "nieskończonego" iteratora/generatora
for (var num of take(fib(), 10)) {
  console.log(num);
}
