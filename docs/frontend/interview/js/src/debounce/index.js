var count = 1
var container = document.getElementById('container')

function getUserAction(e) {
  console.log(this)
  console.log(e)
  container.innerHTML = count++
}

var setUseAction = debounce(getUserAction, 5000, true)

container.onmousemove = setUseAction

document.getElementById('button').addEventListener('click', function() {
  setUseAction.cancel()
})

// 防抖

function debounce(fn, wait, immediate) {
  let timeout = context = args = null
  
  function wrapper() {
    if (timeout) {
      clearTimeout(timeout)
    } else {
      if (immediate) {
        fn.apply(this, arguments)
      } else {
        context = this
        args = arguments
      }
    }
    timeout = setTimeout(() => {
      timeout = null
      if (!immediate) {
        fn.apply(context, args)
        context = args = null
      }
    }, wait)
  }
  wrapper.cancel = function() {
    clearTimeout(timeout)
    timeout = null
  }
  return wrapper
}

