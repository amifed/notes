const STATUS = {
  PENDING: 'pending',
  FULFILLED: 'fulfilled',
  REJECTED: 'rejected',
}
class _Promise {
  constructor(exector) {
    this.PromiseState = STATUS.PENDING
    this.PromiseResult = null
    this.callbacks = []

    const resolve = (result) => {
      if (this.PromiseState !== STATUS.PENDING) return
      this.PromiseState = STATUS.FULFILLED
      this.PromiseResult = result
      setTimeout(() =>
        this.callbacks.forEach(({ onResolved }) => {
          onResolved(result)
        })
      )
    }

    const reject = (result) => {
      if (this.PromiseState !== STATUS.PENDING) return
      this.PromiseState = STATUS.REJECTED
      this.PromiseResult = result
      setTimeout(() =>
        this.callbacks.forEach(({ onReject }) => {
          onReject(result)
        })
      )
    }

    try {
      exector(resolve, reject)
    } catch (e) {
      reject(e)
    }
  }

  then(onResolved, onReject) {
    if (typeof onResolved !== 'function') {
      onResolved = (val) => val
    }
    if (typeof onReject !== 'function') {
      onReject = (err) => {
        throw err
      }
    }
    return new _Promise((resolve, reject) => {
      const callback = (fn) => {
        try {
          const result = fn(this.PromiseResult)
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

      if (this.PromiseState === STATUS.PENDING) {
        this.callbacks.push({
          onResolved: () => callback(onResolved),
          onReject: () => callback(onReject),
        })
      }
      if (this.PromiseState === STATUS.FULFILLED) {
        setTimeout(() => callback(onResolved))
      }
      if (this.PromiseState === STATUS.REJECTED) {
        setTimeout(() => callback(onReject))
      }
    })
  }

  catch(onRejected) {
    return this.then(undefined, onRejected)
  }

  static resolve(result) {
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

  static reject(result) {
    return new Promise((resolve, reject) => reject(result))
  }

  static all(promises) {
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

  static race(promises) {
    return new _Promise((resolve, reject) => {
      for (let i = 0; i < promises.length; ++i) {
        promises.then(
          (val) => resolve(val),
          (err) => reject(err)
        )
      }
    })
  }
}
