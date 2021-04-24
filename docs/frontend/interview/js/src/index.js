function light(color, wait) {
  return new Promise((resolve) => {
    setTimeout(() => {
      console.log(color)
      resolve()
    }, wait)
  })
}

function* gen() {
  yield light('green', 1000)
  yield light('red', 2000)
  yield light('yellow', 3000)
}

function run(iter) {
  const result = iter.next()
  if (result.done) {
    run(gen())
  } else {
    result.value.then(() => run(iter))
  }
}

run(gen())