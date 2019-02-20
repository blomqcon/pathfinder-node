'use strict'
var pathfinderIO = require('./io');

const devMode = true;

let pathfinder;
if (devMode) {
	pathfinder = require('./build/Release/pathfinder-node');
} else if(process.platform == "win32" && process.arch == "x64") {
	pathfinder = require('./pre-built-binaries/winx64/pathfinder-node');
} else {
	throw new Error("No pre-built-binary for your system.");
}

module.exports = {
	core: pathfinder,
	io: pathfinderIO
};