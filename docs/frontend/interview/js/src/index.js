function debounce(fn, wait, immediate) {
  let timeout = null,
    context,
    args
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
      if (!immedaite) {
        fn.apply(context, args)
        context = args = null
      }
    }, wait)
  }
}
function throttle(func, ms) {
  let isThrottled = false,
    savedArgs,
    savedThis

  function wrapper() {
    if (isThrottled) {
      savedArgs = arguments
      savedThis = this
      return
    }

    func.apply(this, arguments)

    isThrottled = true

    setTimeout(function() {
      isThrottled = false
      if (savedArgs) {
        wrapper.apply(savedThis, savedArgs)
        savedArgs = savedThis = null
      }
    }, ms)
  }

  return wrapper
}

