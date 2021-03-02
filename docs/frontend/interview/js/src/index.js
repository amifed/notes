const a = [
  [0, 0],
  [-1, 1],
  [-2, 2],
];

console.log(Math.max(a.map(([a, b]) => b - a)));
