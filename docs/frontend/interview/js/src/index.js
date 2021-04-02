// 方法3
var arr = [1, [2, [3, 4]]]

function flatten(arr) {
  return arr.reduce(
    (prev, next) => prev.concat(Array.isArray(next) ? flatten(next) : next),
    []
  )
}

console.log(flatten([[1]]))
