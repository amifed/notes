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
    {
      title: "数据结构",
      collapsable: false,
      children: ["data-structure/stack"],
    },
  ],
};