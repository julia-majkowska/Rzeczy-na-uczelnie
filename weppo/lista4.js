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
        yield e;
        console.log(e, "**");
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
for (var e of root) {
  console.log(e);
}
