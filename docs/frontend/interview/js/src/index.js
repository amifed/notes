"use strict";

function _inheritsLoose(subClass, superClass) {
  subClass.prototype = Object.create(superClass.prototype);
  subClass.prototype.constructor = subClass;
  _setPrototypeOf(subClass, superClass);
}

function _setPrototypeOf(o, p) {
  _setPrototypeOf =
    Object.setPrototypeOf ||
    function _setPrototypeOf(o, p) {
      o.__proto__ = p;
      return o;
    };
  return _setPrototypeOf(o, p);
}

var Father = /*#__PURE__*/ (function () {
  function Father(name) {
    this.name = name;
  }

  Father.foo = function foo() {
    console.log("father static");
  };

  var _proto = Father.prototype;

  _proto.bar = function bar() {
    console.log("father function");
  };

  return Father;
})();

var Son = /*#__PURE__*/ (function (_Father) {
  _inheritsLoose(Son, _Father);

  function Son(name) {
    return _Father.call(this, name) || this;
  }

  return Son;
})(Father);

var son = new Son("ding");
