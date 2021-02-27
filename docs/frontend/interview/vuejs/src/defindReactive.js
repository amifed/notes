/**
 * 模拟视图更新
 * @param {*} val
 */
function cb(val) {
  // 渲染视图
  console.log("视图更新 ～", val);
}

/**
 * 使对象属性可观察
 * @param {object} obj 响应式对象
 * @param {string} key
 * @param {*} val
 */
function defineReactive(obj, key, val) {
  Object.defineProperty(obj, key, {
    enumerable: true,
    configurable: true,
    get() {
      return val;
    },
    set(newVal) {
      if (newVal === val) return;
      val = newVal;
      cb(newVal);
    },
  });
}

/**
 * 遍历对象所有属性，对每个属性实现响应式
 * @param {object} value 对象
 */
function observer(value) {
  if (!value || typeof value !== "object") return;
  Object.keys(value).forEach((key) => {
    defineReactive(value, key, value[key]);
  });
}

class Vue {
  constructor(options) {
    this._data = options.data;
    observer(this._data);
  }
}

let vm = new Vue({
  data: {
    test: "test value",
  },
});
vm._data.test = "test changed"; // 视图更新 ～ test changed
