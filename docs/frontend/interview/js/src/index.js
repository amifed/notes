const getList = ([x, ...y]) => [x, y]
const getUser = user => {name: user.name}

console.log(getList([1,2,3,4]));
console.log(getUser({name: 'ding'}));