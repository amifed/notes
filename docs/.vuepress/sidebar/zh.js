// var process = require("process");
// if (process.env.NODE_ENV == "production")
//   process.chdir("/home/runner/work/notes/notes");
module.exports = {
  ...require("./contest"),
  ...require("./algorithm"),
  ...require("./solution"),
  ...require("./frontend"),
};
