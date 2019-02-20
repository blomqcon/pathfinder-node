// PathfinderConvert.h
#ifndef PathfinderConvert_H
#define PathfinderConvert_H

#include <nan.h>
#include <pathfinder.h>

class PathfinderConvert
{
 public:
    static Waypoint* allocateWaypoints(v8::Local<v8::Array> waypointObjects);
    static Segment* allocateSegments(v8::Local<v8::Array> segmentsObjects);
    static v8::Local<v8::Array> createTrajectoryArray(Segment* trajectory, int length);
  

 private:
    // Disallow creating an instance of this object
    PathfinderConvert() {}
};

#endif  // PathfinderConvert_H