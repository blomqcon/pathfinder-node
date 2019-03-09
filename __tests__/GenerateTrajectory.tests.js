var path = require('path');
var fs = require('fs');
const pathfinder = require('../index').core;
const pathfinderIO = require('../index').io;

test('Basic-Trajectory-Generation', () => {

    var waypoints = [{x: -4, y: -1, angle: 0}, {x: -1, y: 2, angle: 0}];
    var config = {};

    var trajectory = pathfinder.generateTrajectory(waypoints, config);
    expect(trajectory.length).toBe(1539);
});

test.only('Complex-Trajectory-Generation', () => {
  var waypoints = [{x: 0, y: 0, angle: 1.570795}, {x: 0, y: 100, angle: 1.570795}];
  var config = {
    "splineFitMethod": "FIT_HERMITE_CUBIC",
    "sampleCount": "PATHFINDER_SAMPLES_FAST",
    "dt": 0.1,
    "maxVelocity": 100.0,
    "maxAcceleration": 100.0,
    "maxJerk": 1000000.0
  };

  var trajectory = pathfinder.generateTrajectory(waypoints, config);

  console.log("Length: " + trajectory.length);

  for(var i = 0; i < trajectory.length; i++) {
    console.log(`${trajectory[i].dt}, ${trajectory[i].position}, ${trajectory[i].velocity}, ${trajectory[i].acceleration}, ${trajectory[i].heading}`)
  }

  

})

test('Tank Trajectory Generation', () => {
  var waypoints = [{x: -4, y: -1, angle: 0}, {x: -1, y: 2, angle: 0}];
  var config = {};

  var trajectory = pathfinder.generateTrajectory(waypoints, config);
  var tankTrajectories = pathfinder.generateTankTrajectories(trajectory, "18.0");
  expect(trajectory.length).toBe(1539);
  expect(tankTrajectories.leftTrajectory.length).toBe(1539);
  expect(tankTrajectories.rightTrajectory.length).toBe(1539);
});

test('Trajectory serialization', async () => {
  var waypoints = [{x: -4, y: -1, angle: 0}, {x: -1, y: 2, angle: 0}];
  var config = {};

  var trajectory = pathfinder.generateTrajectory(waypoints, config);

  const testTrajectoryDir = path.resolve(__dirname, "temp/");
  const testTrajectoryFile = path.resolve(testTrajectoryDir, "test_trajectory.csv");
  if (!fs.existsSync(testTrajectoryDir))
    fs.mkdirSync(testTrajectoryDir);
  
  pathfinderIO.serializeTrajectoryCsv(testTrajectoryFile, trajectory);
  var trajectoryFromFile = await pathfinderIO.deserializeTrajectoryCsvAsync(testTrajectoryFile);

  expect(trajectoryFromFile.length).toBe(trajectory.length);
});