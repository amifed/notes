const fs = require("fs");
const path = require("path");
const { getChildFolders } = require("./util");
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

/**
 * 递归生成sidebar
 * @param {string} p 文件夹绝对路径
 * @param {string} parentDirName 父文件夹名
 */
const generator = (p, parentDirName = "") => {
  const ds = fs
    .readdirSync(p, { withFileTypes: true })
    .filter((d) => d && !d.name.startsWith("."));
  let t = [];
  ds.map((d) => {
    if (d.isFile() && d.name.endsWith("md")) {
      const prefix = parentDirName ? parentDirName + "/" : "";
      const name = d.name.substring(0, d.name.lastIndexOf("."));
      t.push(prefix + name);
    } else if (d.isDirectory() && d.name != "src")
      t.push({
        title: d.name,
        collapsable: false,
        children: generator(
          path.join(p, d.name),
          `${parentDirName ? parentDirName + "/" : ""}${d.name}`
        ),
      });
  });
  return t;
};

module.exports = {
  "/contest/leetcode/": [
    "",
    // {
    //   title: "周赛",
    //   collapsable: false,
    //   children: getContestLeetCode().filter((f) => f.startsWith("weekly")),
    // },
    // {
    //   title: "双周赛",
    //   collapsable: false,
    //   children: getContestLeetCode().filter((f) => f.startsWith("biweekly")),
    // },
    ...generator(path.resolve(__dirname, "../../contest/leetcode")).filter(
      (f) => f != "README"
    ),
  ],
  // "/contest/atcoder/": [
  //   "",
  //   {
  //     title: "AtCoder Beginner Contest",
  //     collapsable: false,
  //     children: getContestChildren("atcoder"),
  //   },
  // ],
};
