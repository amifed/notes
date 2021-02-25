console.log(
  new Array(10)
    .map(() => {
      console.log(1);
      Math.random() * 10 - Math.random() * 10;
    })
    .map(parseInt)
);
let ans = [];
for (let i = 0; i < 10; ++i) {
  ans.push(Math.random() * 10 - Math.random() * 10);
}
console.log(ans.map(parseInt));
