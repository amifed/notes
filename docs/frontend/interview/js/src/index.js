const flat = (arr) =>
  Array.isArray(arr) ? arr.reduce((a, b) => [...a, ...flat(b)], []) : [arr];

console.log(flat([1, 2, [3, 4, [5, 6]]]));
