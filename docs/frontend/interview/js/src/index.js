function curry(f) {
  return function curried(...args) {
    if (args.length >= f.length) {
      return f.apply(this, args)
    }
    return function(..._args) {
      return curried.apply(this, args.concat(_args))
    }
  }
} 
//实现 add(1)(2)(3)(4)
function add(a, b, c, d) {
  return a + b + c + d
}
add = curry(add)
console.log(add(1)(2)(3)(4)) // 1+2+3+4
