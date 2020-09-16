const calculate = require('./build/Release/ann_js');

function calc() {

  let i, x = 2.324323, y = 90.21146438;

  for(i = 0; i < 1000000000; ++i)
    x += y;

  const total = x;
  return total;
}

console.time('c++');
calculate.calc();
console.timeEnd('c++');

console.time('js');
calc();
console.timeEnd('js');
