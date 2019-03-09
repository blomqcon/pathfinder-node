var path = require('path');
var fs = require('fs');
const pathfinder = require('../index').core;

var waypoints = [{x: 0, y: 0, angle: 1.570795}, {x: 0, y: 100, angle: 1.570795}];
var config = {
  "splineFitMethod": "FIT_HERMITE_CUBIC",
  "sampleCount": "PATHFINDER_SAMPLES_FAST",
  "dt": 0.01,
  "maxVelocity": 100.0,
  "maxAcceleration": 100.0,
  "maxJerk": 1000000.0
};

var trajectory = pathfinder.generateTrajectory(waypoints, config);

console.log("Length: " + trajectory.length);

for(var i = 0; i < trajectory.length; i++) {
  console.log(`${trajectory[i].dt}, ${trajectory[i].position}, ${trajectory[i].velocity}, ${trajectory[i].acceleration}, ${trajectory[i].heading}`)
}