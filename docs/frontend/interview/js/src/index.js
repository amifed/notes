var name = "World!";
(function() {
  if (typeof name === "undefined") {
    name = "Jack";

    console.log("Goodbye" + name);
  } else {
    console.log("hello" + name);
  }
})();
