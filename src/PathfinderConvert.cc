#include "PathfinderConvert.h"
#include <iostream>

Waypoint* PathfinderConvert::allocateWaypoints(v8::Local<v8::Array> waypointObjects)
{
  Waypoint* waypoints = new Waypoint[waypointObjects->Length()];
  for (unsigned int i = 0; i < waypointObjects->Length(); i++)
  {
    v8::Local<v8::Object> waypointObject = waypointObjects->Get(i).As<v8::Object>();

    // TODO: Be more error tolerent
    v8::MaybeLocal<v8::Value> xValue = waypointObject->GetRealNamedProperty(Nan::GetCurrentContext(), Nan::New("x").ToLocalChecked());
    v8::MaybeLocal<v8::Value> yValue = waypointObject->GetRealNamedProperty(Nan::GetCurrentContext(), Nan::New("y").ToLocalChecked());
    v8::MaybeLocal<v8::Value> angleValue = waypointObject->GetRealNamedProperty(Nan::GetCurrentContext(), Nan::New("angle").ToLocalChecked());

    v8::Local<v8::Number> xNumber = xValue.ToLocalChecked().As<v8::Number>();
    v8::Local<v8::Number> yNumber = yValue.ToLocalChecked().As<v8::Number>();
    v8::Local<v8::Number> angleNumber = angleValue.ToLocalChecked().As<v8::Number>();

    waypoints[i] = { xNumber->Value(), yNumber->Value(), angleNumber->Value() };

    std::cout << "Waypoint: " << angleNumber->Value() << "\n";
  }
  
  return waypoints;
}

Segment* PathfinderConvert::allocateSegments(v8::Local<v8::Array> segmentsObjects)
{
  Segment* segments = new Segment[segmentsObjects->Length()];
  for (unsigned int i = 0; i < segmentsObjects->Length(); i++)
  {
    v8::Local<v8::Object> segmentObject = segmentsObjects->Get(i).As<v8::Object>();

    // TODO: Be more error tolerent
    double dt = Nan::Get(segmentObject, Nan::New("dt").ToLocalChecked()).ToLocalChecked().As<v8::Number>()->Value();
    double x = Nan::Get(segmentObject, Nan::New("x").ToLocalChecked()).ToLocalChecked().As<v8::Number>()->Value();
    double y = Nan::Get(segmentObject, Nan::New("y").ToLocalChecked()).ToLocalChecked().As<v8::Number>()->Value();
    double position = Nan::Get(segmentObject, Nan::New("position").ToLocalChecked()).ToLocalChecked().As<v8::Number>()->Value();
    double velocity = Nan::Get(segmentObject, Nan::New("velocity").ToLocalChecked()).ToLocalChecked().As<v8::Number>()->Value();
    double acceleration = Nan::Get(segmentObject, Nan::New("acceleration").ToLocalChecked()).ToLocalChecked().As<v8::Number>()->Value();
    double jerk = Nan::Get(segmentObject, Nan::New("jerk").ToLocalChecked()).ToLocalChecked().As<v8::Number>()->Value();
    double heading = Nan::Get(segmentObject, Nan::New("heading").ToLocalChecked()).ToLocalChecked().As<v8::Number>()->Value();

    segments[i] = { dt, x, y, position, velocity, acceleration, jerk, heading };
  }
  return segments;
}

v8::Local<v8::Array> PathfinderConvert::createTrajectoryArray(Segment* trajectory, int length)
{
  v8::Local<v8::Array> trajectoryArray = Nan::New<v8::Array>();
    for (int i = 0; i < length; i++ ) {
      Segment segment = trajectory[i];
      v8::Local<v8::Object> segmentObject = Nan::New<v8::Object>();
      
      Nan::Set(segmentObject, Nan::New("dt").ToLocalChecked(), Nan::New(segment.dt));
      Nan::Set(segmentObject, Nan::New("x").ToLocalChecked(), Nan::New(segment.x));
      Nan::Set(segmentObject, Nan::New("y").ToLocalChecked(), Nan::New(segment.y));
      Nan::Set(segmentObject, Nan::New("position").ToLocalChecked(), Nan::New(segment.position));
      Nan::Set(segmentObject, Nan::New("velocity").ToLocalChecked(), Nan::New(segment.velocity));
      Nan::Set(segmentObject, Nan::New("acceleration").ToLocalChecked(), Nan::New(segment.acceleration));
      Nan::Set(segmentObject, Nan::New("jerk").ToLocalChecked(), Nan::New(segment.jerk));
      Nan::Set(segmentObject, Nan::New("heading").ToLocalChecked(), Nan::New(segment.heading));

      trajectoryArray->Set(i, segmentObject);
    }
    return trajectoryArray;
}
