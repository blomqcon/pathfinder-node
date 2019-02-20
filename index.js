'use strict'
var bindings = require('bindings');

// TODO: Figure out how to configure this so that dev
//       machines (C++ toolchain setup) build the
//       binary but other machines use the prebuilt binaries.
var pathfinder;
// if(process.platform == "win32" && process.arch == "x64") {
//     // Load the precompiled binary for windows x64.
// 	pathfinder = require('./bin/winx64/pathfinder-node');
// } else {
	// Load the new built binary for other platforms.
	pathfinder = bindings('pathfinder-node');
// }

module.exports = pathfinder;
