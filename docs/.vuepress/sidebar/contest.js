const fs = require("fs");
const path = require("path");
const { getChildFolders } = require("./util");

const getContestChildren = (dirname) => {
  const p = path.resolve(__dirname, `../../contest/${dirname}`);
  return getChildFolders(p)
    .filter((d) => fs.existsSync(path.join(p, d, "README.md")))
    .map((d) => d + "/");
};

module.exports = {
  "/contest/leetcode/": [
    "",
    {
      title: "周赛",
      collapsable: false,
      children: getContestChildren("leetcode").filter(
        (f) => !f.includes("biweekly")
      ),
    },
    {
      title: "双周赛",
      collapsable: true,
      children: getContestChildren("leetcode").filter((f) =>
        f.includes("biweekly")
      ),
    },
  ],
  "/contest/atcoder/": [
    "",
    {
      title: "AtCoder Beginner Contest",
      collapsable: false,
      children: getContestChildren("atcoder"),
    },
  ],
};
