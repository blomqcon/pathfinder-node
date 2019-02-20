var path = require('path');
var fs = require('fs');
const pathfinder = require('../index').core;
const pathfinderIO = require('../index').io;

test('Basic Trajectory Generation', () => {

    var waypoints = [{x: -4, y: -1, angle: 0}, {x: -1, y: 2, angle: 0}];
    var config = {};

    var trajectory = pathfinder.generateTrajectory(waypoints, config);
    expect(trajectory.length).toBe(1539);
});

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