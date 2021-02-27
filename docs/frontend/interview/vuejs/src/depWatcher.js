class Dep {
  constructor() {
    // 用来存放 Watcher 对象的数组
    this.subs = [];
  }
  addSub(sub) {
    this.subs.push(sub);
  }
  /* 通知所有 Watcher 对象更新视图 */
  notify() {
    this.subs.forEach((sub) => sub.update());
  }
}

class Watcher {
  constructor() {
    // 在 new Watcher() 时将该对象赋值给 Dep.target，在 get 中会用到
    Dep.target = this;
  }
  /* 视图更新方法 */
  update() {
    console.log("更新视图啦 ～");
  }
}

Dep.target = null;

function defineReactive(obj, key, val) {
  const dep = new Dep();

  Object.defineProperty(obj, key, {
    enumerable: true,
    configurable: true,
    get() {
      dep.addSub(Dep.target);
      return val;
    },
    set(newVal) {
      if (newVal === val) return;
      val = newVal;
      dep.notify();
    },
  });
}

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

    new Watcher();

    // 在 render 过程中，会访问对象属性，触发 get 函数，并将观察着加入订阅列表
    console.log("render ~", this._data.test);
  }
}

let vm = new Vue({
  data: {
    test: "test value",
  },
}); // render ~ test value
vm._data.test = "test changed"; // 视图更新啦 ～
