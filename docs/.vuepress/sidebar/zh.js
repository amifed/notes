const fs = require("fs");
const path = require("path");

/**
 * 获取绝对路径的文件夹下的文件名
 * @param {string} path 绝对路径
 */
const getFolderMdFilenames = (path) =>
  fs
    .readdirSync(path, { withFileTypes: true })
    .filter((f) => f.isFile() && f.name.endsWith("md"))
    .map((f) => f.name.substring(0, f.name.lastIndexOf(".")));

/**
 * 获取绝对路径下子文件夹名
 * @param {string} path 绝对路径
 */
const getChildFolders = (path) => {
  try {
    return fs
      .readdirSync(path, { withFileTypes: true })
      .filter((d) => d.isDirectory())
      .map((d) => d.name);
  } catch (error) {}
};

const getAlgorithmSidebar = () => {
  const files = fs
    .readdirSync(path.resolve(__dirname, "../../algorithm"), {
      withFileTypes: true,
    })
    .filter((d) => d.isDirectory())
    .map((dir) => {
      return [
        `/algorithm/${dir.name}/`,
        [
          "",
          ...getFolderMdFilenames(
            path.resolve(__dirname, `../../algorithm/${dir.name}`)
          ).filter((f) => f != "README"),
        ],
      ];
    });
  return Object.fromEntries(new Map(files));
};

const getContestChildren = (dirname) => {
  const p = path.resolve(__dirname, `../../contest/${dirname}`);
  return getChildFolders(p)
    .filter((d) => fs.existsSync(path.join(p, d, "README.md")))
    .map((d) => d + "/");
};

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
  ...getAlgorithmSidebar(),
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
    {
      title: "AtCoder Beginner Contest",
      collapsable: false,
      children: getContestChildren("atcoder"),
    },
  ],
  "/solution/acwing/": [
    "",
    ...generator(path.resolve(__dirname, "../../solution/acwing")).filter(
      (f) => f != "README"
    ),
  ],
};
