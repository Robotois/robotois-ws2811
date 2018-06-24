// myobject.h
#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <node.h>
#include <node_object_wrap.h>

// #include "../LEDStrip/LEDStrip.h"

class MyObject : public node::ObjectWrap {
 public:
  static void Init(v8::Local<v8::Object> exports);

 private:
  explicit MyObject(int width = 1, int height = 1, uint8_t brightness = 128, uint8_t pin = 1);
  ~MyObject();

  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
  // static void PlusOne(const v8::FunctionCallbackInfo<v8::Value>& args);
  static v8::Persistent<v8::Function> constructor;
  // double value_;
  static void ledOn(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void ledOff(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void release(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void allLedOn(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void allLedOff(const v8::FunctionCallbackInfo<v8::Value>& args);
};


#endif
