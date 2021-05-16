// 实现
function reactive(obj) {
  // ...res
  const proxyObj = {}
  const subs = []
  for (let key in obj) {
    if (obj.hasOwnProperty(key)) {
      Object.defineProperty(proxyObj, key, {
        enumerable: true,
        configurable: true,
        get() {
          return obj[k]
        },
        set(newVal) {
          if (newVal == obj[key]) return
          obj[key] = newVal
          subs.forEach((fn) => fn(obj, key))
        },
      })
    }
  }
  proxyObj.subscribe = function(fn) {
    subs.push(fn)
  }
  return proxyObj
}
// 用例
const obj1 = reactive({
  a: 1,
  b: 2,
})
obj1.subscribe((newState, key) => {
  console.log(newState, key) // {a:3,b:2} 'a'
  // {a:3,b:4} 'b'
})

obj1.subscribe((newState, key) => {
  console.log(newState, key) // {a:3,b:2} 'a'
  // {a:3,b:4} 'b'
})

obj1.a = 3
obj1.b = 4
