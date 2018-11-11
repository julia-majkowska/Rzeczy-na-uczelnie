//zadanie1

var Tree = {
  init: function(left, right, val) {
    this.left = left;
    this.right = right;
    this.val = val;
  },

  infixPrint: function() {
    if (this.left) this.left.infixPrint();
    console.log(" |" + this.val + "| ");
    if (this.right) this.right.infixPrint();
  },
  [Symbol.iterator]: function*() {
    if (this.left) {
      for (var e in this.left) {
        console.log(e, "**");
        yield e;
      }
    }
    yield this.val;

    if (this.right) {
      for (var e in this.right) {
        console.log(e, "**");
        yield e;
      }
    }
  }
};

var t1 = Object.create(Tree);
var t2 = Object.create(Tree);
var t3 = Object.create(Tree);

t3.init(null, null, "lisc");
t2.init(null, t3, "Srodek");
t1.init(null, t2, "korzen");
t1.infixPrint();

//zadanie2
var root = t1;
// enumeracja wartości z węzłów
root.infixPrint();
for (var e of root) {
  console.log(e);
}

//zadanie5
var readline = require("readline");
var rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
  terminal: false
});

rl.on("line", function(line) {
  console.log(`Witaj ${line}$`);
});

//zadanie6

var fs = require("fs");
var content = fs.readFileSync('myfile.txt', 'utf8');
console.log(content);

//zadanie7 
counters = {}
const rl = readline.createInterface({
    input: fs.createReadStream('sample.txt'),
    crlfDelay: Infinity
  });
  
  rl.on('line', (line) => {
    console.log(`Line from file: ${line}`);
  });