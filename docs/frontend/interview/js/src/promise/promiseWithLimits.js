// Promise 实现控制并发请求

/**
 * Promise 实现控制并发请求
 * @param {*} promises 返回 Promise 对象的异步函数
 * @param {*} limits 并发数量
 * @returns
 */
function fetchWithLimits(promises, limits = 1) {
  const ps = promises.slice()
  // 对应请求和结果顺序
  const mp = new WeakMap()

  function run() {
    if (ps.length) {
      const p = ps.shift()
      p().then((res) => {
        mp.set(p, res)
        run()
      })
    }
  }

  // 设置并发请求数
  const runs = Array(Math.min(limits, promises.length))
    .fill(Promise.resolve())
    .map((promise) => promise.then(run))

  return Promise.all(runs).then(() => promises.map((e) => mp.get(e)))
}
