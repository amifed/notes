const fs = require("fs");
const path = require("path");

const getFolderMdFilenames = (path) =>
  fs
    .readdirSync(path, { withFileTypes: true })
    .filter((f) => f.isFile() && f.name.endsWith("md"))
    .map((f) => f.name.substring(0, f.name.lastIndexOf(".")));

const p = path.resolve(__dirname, "../../solution/acwing");

console.log(p);

const generator = (p, parentDirName = "") => {
  console.log(p);
  const ds = fs
    .readdirSync(p, { withFileTypes: true })
    .filter((d) => d && !d.name.startsWith("."));
  let t = [];
  ds.map((d) => {
    if (d.isFile() && d.name.endsWith("md")) {
      const prefix = parentDirName ? parentDirName + "/" : "";
      const name = d.name.substring(0, d.name.lastIndexOf("."));
      t.push(prefix + name);
    } else if (d.isDirectory()) {
      const children = generator(
        path.join(p, d.name),
        `${parentDirName ? parentDirName + "/" : ""}${d.name}`
      );
      if (children.length) {
        t.push({
          title: d.name,
          collapsable: false,
          children,
        });
      }
    }
  });
  return t;
};

console.log(
  JSON.stringify(
    generator("/Users/jinyang/Code/notes/docs/solution/acwing").map((f) =>
      typeof f === "string" && f === "README" ? "" : f
    )
  )
);
