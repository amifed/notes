function PromiseRace(arr) {
  return new Promise((resolve, reject) => {
    for (let i = 0; i < arr.length; ++i) {
      Promise.resolve(arr[i])
        .then((res) => resolve(res))
        .catch((err) => reject(err))
    }
  })
}
