let cnt = 1
const container = document.querySelector('#container')

function getUserAction(e) {
  console.log(e)
  container.innerHTML = cnt++
}

function debounce(fn, wait = 50, immediate = false) {
  let timeout, context, args, result

  const later = () =>
    setTimeout(() => {
      timeout = null
      if (!immediate) {
        fn.apply(context, args)
        context = args = null
      }
    }, wait)

  const debounced = function() {
    if (timeout) {
      clearTimeout(timeout)
      timeout = later()
    } else {
      if (immediate) {
        result = fn.apply(this, arguments)
      } else {
        context = this
        args = arguments
      }
      timeout = later()
    }
    return result
  }

  debounced.cancel = function() {
    clearTimeout(timeout)
    timeout = null
  }

  return debounced
}

const setUserAction = debounce(getUserAction, 10000, true)

container.onmousemove = setUserAction

document.querySelector('#cancel').addEventListener('click', () => {
  setUserAction.cancel()
})