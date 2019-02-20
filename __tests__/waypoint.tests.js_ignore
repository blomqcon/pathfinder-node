const pathfinder = require('../index');
const Waypoint = pathfinder.Waypoint;

test('Construct waypoint with function API', () => {
    var waypointDefault = Waypoint();
    expect(waypointDefault.x).toBe(0);
    expect(waypointDefault.y).toBe(0);
    expect(waypointDefault.angle).toBe(0);

    var waypoint2 = Waypoint(2, 2);
    expect(waypoint2.x).toBe(2);
    expect(waypoint2.y).toBe(2);
    expect(waypoint2.angle).toBe(0);

    var waypoint3 = Waypoint(3, 3, 3);
    expect(waypoint3.x).toBe(3);
    expect(waypoint3.y).toBe(3);
    expect(waypoint3.angle).toBe(3);
  });

  test('Construct waypoint with constructor API', () => {
    var waypointDefault = new Waypoint();
    expect(waypointDefault.x).toBe(0);
    expect(waypointDefault.y).toBe(0);
    expect(waypointDefault.angle).toBe(0);

    var waypoint2 = new Waypoint(2, 2);
    expect(waypoint2.x).toBe(2);
    expect(waypoint2.y).toBe(2);
    expect(waypoint2.angle).toBe(0);

    var waypoint3 = new Waypoint(3, 3, 3);
    expect(waypoint3.x).toBe(3);
    expect(waypoint3.y).toBe(3);
    expect(waypoint3.angle).toBe(3);
  });

  test('Construct waypoint with non-number constructor', () => {
    expect(() => {
      var waypoint = new Waypoint("string", "string");
    }).toThrowError();

    expect(() => {
      var waypoint = Waypoint("string", "string");
    }).toThrowError();
  });

  test('Waypoint property number assignment', () => {
    var waypoint = new Waypoint(10.0, 10.0, 3.14);
    
    waypoint.x = 11.0;
    expect(waypoint.x).toBe(11.0);
    
    waypoint.y = 12.0;
    expect(waypoint.y).toBe(12.0);

    waypoint.angle = 0.0;
    expect(waypoint.angle).toBe(0.0);
  });

  test('Waypoint property non-number assignment', () => {
    var waypoint = new Waypoint(10.0, 10.0, 3.14);
    
    expect(() => {
      waypoint.x = "string";
    }).toThrowError(TypeError);

    expect(() => {
      waypoint.y = "string";
    }).toThrowError(TypeError);

    expect(() => {
      waypoint.angle = "string";
    }).toThrowError(TypeError);
  });
