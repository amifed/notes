const fs = require("fs");
const path = require("path");
const { getChildFolders } = require("./util");
const { getContestLeetCode } = require(path.resolve(
  process.env.PWD,
  `./docs/contest/index`
));

const getContestChildren = (dirname) => {
  const p = path.resolve(__dirname, `../../contest/${dirname}`);
  return getChildFolders(p)
    .filter((d) => fs.existsSync(path.join(p, d, "README.md")))
    .sort((a, b) => (a < b ? 1 : -1))
    .map((d) => d + "/");
};

const getContestSidebar = () => {
  const files = fs
    .readdirSync(path.resolve(__dirname, "../../contest"), {
      withFileTypes: true,
    })
    .filter((d) => d.isDirectory())
    .map((dir) => {
      return [
        `/contest/${dir.name}/`,
        [
          "",
          ...getFolderMdFilenames(
            path.resolve(__dirname, `../../contest/${dir.name}`)
          ).filter((f) => f != "README"),
        ],
      ];
    });
  return Object.fromEntries(new Map(files));
};

module.exports = {
  "/contest/leetcode/": [
    "",
    {
      title: "周赛",
      collapsable: false,
      children: getContestLeetCode().filter((f) => f.startsWith("weekly")),
    },
    {
      title: "双周赛",
      collapsable: false,
      children: getContestLeetCode().filter((f) => f.startsWith("biweekly")),
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
