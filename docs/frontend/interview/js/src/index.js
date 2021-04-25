function _Promise(executor) {
  this.PromiseState = 'pending'
  this.PromiseResult = null
  this.callbacks = []

  // resolve
  const resolve = (data) => {
    if (this.PromiseState !== 'pending') return
    // 1 修改状态 （PromiseState）
    this.PromiseState = 'fulfilled'
    // 2 设置结果值 （PromiseResult）
    this.PromiseResult = data
    this.callbacks.forEach(({ onResolved }) => {
      onResolved(data)
    })
  }

  // reject
  const reject = (data) => {
    if (this.PromiseState !== 'pending') return
    this.PromiseState = 'rejected'
    this.PromiseResult = data
    this.callbacks.forEach(({ onRejected }) => {
      onRejected(data)
    })
  }

  try {
    // 「同步」调用执行器函数
    executor(resolve, reject)
  } catch (e) {
    reject(e)
  }
}

_Promise.prototype.then = function(onResolved, onRejected) {
  if (typeof onResolved !== 'function') {
    onResolved = (val) => val
  }
  if (typeof onRejected !== 'function') {
    onRejected = (err) => {
      throw err
    }
  }
  return new _Promise((resolve, reject) => {
    const callback = (fn) => {
      try {
        let result = fn(this.PromiseResult)
        if (result instanceof _Promise) {
          result.then(
            (val) => resolve(val),
            (err) => reject(err)
          )
        } else {
          resolve(result)
        }
      } catch (e) {
        reject(e)
      }
    }
    // 调用回调函数
    if (this.PromiseState === 'fulfilled') {
      callback(onResolved)
    }
    if (this.PromiseState === 'rejected') {
      callback(onRejected)
    }
    // pending 保存回调函数
    if (this.PromiseState === 'pending') {
      this.callbacks.push({
        onResolved: () => callback(onResolved),
        onRejected: () => callback(onRejected),
      })
    }
  })
}

_Promise.prototype.catch = function(onRejected) {
  return this.then(undefined, onRejected)
}

_Promise.resolve = function(result) {
  return new _Promise((resolve, reject) => {
    if (result instanceof _Promise) {
      result.then(
        (val) => resolve(val),
        (err) => reject(err)
      )
    } else {
      resolve(result)
    }
  })
}

_Promise.reject = function(result) {
  return new _Promise((resolve, reject) => {
    reject(result)
  })
}

_Promise.all = function(promises) {
  return new _Promise((resolve, reject) => {
    let cnt = 0
    const ans = []
    for (let i = 0; i < promises.length; ++i) {
      promises[i].then(
        (val) => {
          ++cnt
          ans[i] = val
          if (cnt === promises.length) {
            resolve(ans)
          }
        },
        (err) => reject(err)
      )
    }
  })
}

_Promise.race = function(promises) {
  
}