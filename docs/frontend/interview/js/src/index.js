function promiseAll(arr) {
  return new Promise((resolve, reject) => {
    let ans = []
    let cnt = 0
    for (let i = 0; i < arr.length; ++i) {
      Promise.resolve(arr[i])
        .then((res) => {
          ans[i] = res
          if (++cnt === arr.length) {
            resolve(ans)
          }
        })
        .catch((err) => reject(err))
    }
  })
}
