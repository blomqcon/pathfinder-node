// WaypointObject.h
#ifndef WaypointObject_H
#define WaypointObject_H

#include <nan.h>
#include <pathfinder.h>

class WaypointObject : public Nan::ObjectWrap {
    public:
        static NAN_MODULE_INIT(Init);
    private:
        explicit WaypointObject(Waypoint value);
        ~WaypointObject();

        static NAN_METHOD(New);

        static NAN_GETTER(GetX);
        static NAN_SETTER(SetX);

        static NAN_GETTER(GetY);
        static NAN_SETTER(SetY);

        static NAN_GETTER(GetAngle);
        static NAN_SETTER(SetAngle);

        static double GetNumberParameter(Nan::NAN_METHOD_ARGS_TYPE info, int paramIndex);
        static double GetNumberSetter(v8::Local<v8::Value> value);

        static inline Nan::Persistent<v8::Function>& constructor() {
            static Nan::Persistent<v8::Function> my_constructor;
            return my_constructor;
        }

        Waypoint value_;
};

#endif  // WaypointObject_H