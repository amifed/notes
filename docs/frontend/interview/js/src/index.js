// 'http://www.domain.com/order?user=anonymous&id=123&id=456&city=%E5%8C%97%E4%BA%AC&enabled#hash'
const parse = (url) => {
  url = decodeURI(url) // 对 中文 url 解码
  const params = url
    .split('?')[1]
    .split('#')[0]
    .split('&')
  const obj = {}
  for (let s of params) {
    let [k = '', v = true] = s.split('=')
    if (obj.hasOwnProperty(k)) {
      ((Array.isArray(obj[k]) ? obj[k] : (obj[k] = [obj[k]])).push(v))
    } else {
      obj[k] = v
    }
  }
  return obj
}
console.log(
  parse(
    'http://www.domain.com/order?user=anonymous&id=123&id=456&id=789&city=%E5%8C%97%E4%BA%AC&enabled#hash'
  )
)
