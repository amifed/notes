const fs = require("fs");
const path = require("path");
const { getFolderMdFilenames } = require("./util");

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

module.exports = {
  ...getAlgorithmSidebar(),
};