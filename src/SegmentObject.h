// SegmentObject.h
#ifndef SegmentObject_H
#define SegmentObject_H

#include <nan.h>
#include <pathfinder.h>

class SegmentObject : public Nan::ObjectWrap {
    public:
        static NAN_MODULE_INIT(Init);
    private:
        explicit SegmentObject(Segment value);
        ~SegmentObject();

        static NAN_METHOD(New);

        static NAN_GETTER(GetDt);
        static NAN_SETTER(SetDt);

        static NAN_GETTER(GetX);
        static NAN_SETTER(SetX);

        static NAN_GETTER(GetY);
        static NAN_SETTER(SetY);

        static NAN_GETTER(GetPosition);
        static NAN_SETTER(SetPosition);

        static NAN_GETTER(GetVelocity);
        static NAN_SETTER(SetVelocity);

        static NAN_GETTER(GetAcceleration);
        static NAN_SETTER(SetAcceleration);

        static NAN_GETTER(GetJerk);
        static NAN_SETTER(SetJerk);

        static NAN_GETTER(GetHeading);
        static NAN_SETTER(SetHeading);

        static double GetNumberParameter(Nan::NAN_METHOD_ARGS_TYPE info, int paramIndex);
        static double GetNumberSetter(v8::Local<v8::Value> value);

        static inline Nan::Persistent<v8::Function>& constructor() {
            static Nan::Persistent<v8::Function> my_constructor;
            return my_constructor;
        }

        Segment value_;
};

#endif  // SegmentObject_H