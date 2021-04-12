function* gen() {
  var result = yield Promise.resolve(true)
  console.log(result)
  return result
}
let g = gen()
console.log(g.next(g.next().value))
