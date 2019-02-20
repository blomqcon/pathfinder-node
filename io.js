'use strict'
// Ideally this logic is implemented by the addon.
// Having trouble getting pathfinder.pathfinder_serialize_csv working though.
//https://github.com/JacisNonsense/Pathfinder/blob/master/Pathfinder-Core/src/io.c

var fs = require('fs');
var os = require('os')
var readline = require('readline');

const CSV_LEADING_STRING = "dt,x,y,position,velocity,acceleration,jerk,heading";	

function serializeTrajectoryCsv(filename, trajectory) {
	var fileStream = fs.createWriteStream(filename, {'flags': 'w'});
	
	fileStream.write(`${CSV_LEADING_STRING}${os.EOL}`);
	for(let i = 0; i < trajectory.length; i++) {
		let segment = trajectory[i];
		let segementValues = `${segment.dt},${segment.x},${segment.y},${segment.position},${segment.velocity},${segment.acceleration},${segment.jerk},${segment.heading}${os.EOL}`;
		fileStream.write(segementValues);
	}
}

function deserializeTrajectoryCsvAsync(filename) {
	return new Promise(function(resolve, reject) {
		let segments = [];
		var lineReader = readline.createInterface({
			input: fs.createReadStream(filename)
		});
		  
		lineReader.on('line', function (segmentLine) {
			// skip the csv heading
			if (segmentLine === CSV_LEADING_STRING)
				return;

			var segmentValues = segmentLine.split(',');
			segments.push({
				dt: segmentValues[0],
				x: segmentValues[1],
				y: segmentValues[2],
				position: segmentValues[3],
				velocity: segmentValues[4],
				acceleration: segmentValues[5],
				jerk: segmentValues[6],
				heading: segmentValues[7]
			});
		});
	
		lineReader.on('close', function() {
			resolve(segments);
		});
	});
}

module.exports = {
	serializeTrajectoryCsv: serializeTrajectoryCsv,
	deserializeTrajectoryCsvAsync: deserializeTrajectoryCsvAsync
};
