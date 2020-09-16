#include <node.h>

namespace ann_js {

  using v8::FunctionCallbackInfo;
  using v8::Isolate;
  using v8::Local;
  using v8::Object;
  using v8::Number;
  using v8::Value;

  void Method( const FunctionCallbackInfo<Value>&args) {

    Isolate* isolate = args.GetIsolate();

    double x = 2.324323, y = 90.21146438;

    for(int i = 0; i < 1000000000; ++i)
      x += y;

    auto total = Number::New(isolate, x);
    args.GetReturnValue().Set(total);

  }

  void Initialize(Local<Object> exports) {
    NODE_SET_METHOD(exports, "calc", Method);
  }

  NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize);

}
