// // 防抖

// function debounce(fn, wait) {
//   let timeout = null
//   return function() {
//     if (timeout) clearTimeout(timeout)
//     timeout = setTimeout(() => fn.apply(this, arguments), wait)
//   }
// }

var count = 1
var container = document.getElementById('container')

function getUserAction(e) {
  console.log(this)
  console.log(e)
  container.innerHTML = count++
}

container.onmousemove = debounce(getUserAction, 1000, false)

// 防抖

function debounce(fn, wait, immediate) {
  let context,
    args,
    timeout = null
  return function() {
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
      }
    }, wait)
  }
}

// 防抖可取消

function debounce(fn, wait, immediate) {
  let timeout = (context = args = null)

  function debounced() {
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

  debounced.cancel = function() {
    clearTimeout(timeout)
    timeout = null
  }

  return debounced
}
