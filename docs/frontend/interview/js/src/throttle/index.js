var count = 1
var container = document.getElementById('container')

function getUserAction(e) {
  console.log(this)
  console.log(e)
  container.innerHTML = count++
}

container.onmousemove = throttle(getUserAction, 2000, true)

// 节流

function throttle(fn, wait) {
  let timeout = (context = args = null)
  return function wrapper() {
    if (timeout) {
      context = this
      args = arguments
      return
    }
    fn.apply(this, arguments)
    timeout = setTimeout(() => {
      timeout = null
      if (args) wrapper.apply(context, args)
      context = args = null
    }, wait)
  }
}
