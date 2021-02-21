const STATUS = {
  PENDING: "pending",
  RESOLVE: "fulfilled",
  REJECT: "rejected",
};
class _Promise {
  static resolve(value) {
    if (value && value.then) {
      return value;
    }
    return new _Promise((resolve) => resolve(value));
  }
  constructor(fn) {
    this.value = undefined;
    this.error = undefined;
    this.stauts = STATUS.PENDING;

    this.resolveFns = [];
    this.rejectFns = [];

    const resolve = (val) => {
      setTimeout(() => {
        this.stauts = STATUS.RESOLVE;
        this.value = val;
        this.resolveFns.forEach(({ fn, resolve, reject }) => resolve(fn(val)));
      });
    };

    const reject = (err) => {
      setTimeout(() => {
        this.stauts = STATUS.REJECT;
        this.error = err;
        this.rejectFns.forEach(({ fn, resolve, reject }) => reject(fn(val)));
      });
    };

    fn(resolve, reject);
  }

  then(fn) {
    if (this.stauts === STATUS.PENDING) {
      return new _Promise((resolve, reject) => {
        this.resolveFns.push({ fn, resolve, reject });
      });
    }
    if (this.stauts === STATUS.RESOLVE) {
      return _Promise.resolve(fn(this.value));
    }
  }

  catch(fn) {
    if (this.stauts === STATUS.PENDING) {
      return new _Promise((resolve, reject) => {
        this.rejectFns.push({ fn, resolve, reject });
      });
    }
    if (this.stauts === STATUS.REJECT) {
      return _Promise.resolve(fn(this.value));
    }
  }
}

_Promise
  .resolve(10)
  .then((o) => o * 10)
  .then((o) => o + 10)
  .then((o) => {
    console.log(o);
  });
