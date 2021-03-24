Function.prototype._apply = function(context, args) {
  context = context ?? globalThis
  context.fn = this
  const result = args ? context.fn(...args) : context.fn()
  delete context.fn
  return result
}

function f(a) {
  console.log(a)
}
f._apply(null, [1])
