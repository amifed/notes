const fs = require("fs");
const path = require("path");
const { getChildFolders, getFolderMdFilenames } = require("./util");

const getContestChildren = (dirname) => {
  const p = path.resolve(__dirname, `../../competition/${dirname}`);
  return getChildFolders(p)
    .filter((d) => fs.existsSync(path.join(p, d, "README.md")))
    .sort((a, b) => (a < b ? 1 : -1))
    .map((d) => d + "/");
};

const getLeetCode = () => {
  return getFolderMdFilenames(
    path.resolve(__dirname, "../../competition/leetcode")
  );
};

module.exports = {
  "/competition/leetcode/": [
    "",
    {
      title: "周赛",
      collapsable: false,
      children: getLeetCode().filter((f) => f.startsWith("weekly")),
    },
    {
      title: "双周赛",
      collapsable: false,
      children: getLeetCode().filter((f) => f.startsWith("biweekly")),
    },
  ],
  "/competition/atcoder/": [
    "",
    {
      title: "AtCoder Beginner Contest",
      collapsable: false,
      children: getContestChildren("atcoder"),
    }, 
  ],
};
console.log(getContestChildren("atcoder"));
