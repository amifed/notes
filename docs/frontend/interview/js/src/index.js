function red() {
  console.log('red')
}
function green() {
  console.log('green')
}
function yellow() {
  console.log('yellow')
}

const light = (wait, cb) =>
  new Promise((resolve) =>
    setTimeout(() => {
      cb()
      resolve()
    }, wait)
  )

function *gen() {
  yield light(3000, red)
  yield light(1000, green)
  yield light(2000, yellow)
}

function step(iterator) {
  const result = iterator.next()
  if (result.done) {
    step(gen())
  } else {
    result.value.then(() => step(iterator))
  }
}

step(gen()) 
