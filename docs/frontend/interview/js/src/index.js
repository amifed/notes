'use strict'

var _add = _interopRequireDefault(require('./add.js'))

var _minus = require('./minus.js')

function _interopRequireDefault(obj) {
  return obj && obj.__esModule ? obj : { default: obj }
}

var sum = (0, _add['default'])(1, 2)
var div = (0, _minus.minus)(2, 1)
console.log('sum: ', sum)
console.log('div: ', div)

Object.defineProperty(exports, '__esModule', { value: true })
exports['default'] = _default
function _default(a, b) {
  return a + b
}

Object.defineProperty(exports, '__esModule', { value: true })
exports.minus = void 0
var minus = function minus(a, b) {
  return a - b
}
exports.minus = minus
