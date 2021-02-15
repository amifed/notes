const path = require("path");
const { generator } = require("./util");

module.exports = {
  "/frontend/interview/": [
    "",
    ...generator(path.resolve(__dirname, "../../frontend/interview")).filter(
      (f) => f !== "README"
    ),
  ],
  "/frontend/algorithm/": [
    "",
    ...generator(path.resolve(__dirname, "../../frontend/algorithm")).filter(
      (f) => f !== "README"
    ),
  ],
};