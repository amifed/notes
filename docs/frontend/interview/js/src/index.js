function _instanceof(obj, F) {
  let proto = obj.__proto__;
  const prototype = F.prototype;
  while (proto) {
    if (proto === prototype) return true;
    proto = proto.__proto__;
  }
  return false;
}
console.log(_instanceof([], Object));
