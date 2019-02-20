// TrajectoryObject.h
#ifndef TrajectoryObject_H
#define TrajectoryObject_H

#include <nan.h>
#include <pathfinder.h>

class TrajectoryObject : public Nan::ObjectWrap {
    public:
        static NAN_MODULE_INIT(Init);
    private:
        explicit TrajectoryObject(Segment value[]);
        ~TrajectoryObject();

        static NAN_METHOD(New);

        static NAN_GETTER(GetSegments);
        static NAN_SETTER(SetSegments);

        static inline Nan::Persistent<v8::Function>& constructor() {
            static Nan::Persistent<v8::Function> my_constructor;
            return my_constructor;
        }

        Segment value_[];
};

#endif  // TrajectoryObject_H