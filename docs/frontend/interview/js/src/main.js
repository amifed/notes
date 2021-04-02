function unique(array) {
  var obj = {};
  return array.filter(function(item, index, array){
      return obj.hasOwnProperty(typeof item + item) ? false : (obj[typeof item + item] = true)
  })
}
console.log(unique([1, 2, 1, 1, NaN, NaN]));